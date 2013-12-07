#include "statemachine.hpp"

as::StateMachine* statemachine = new as::StateMachine();

as::StateMachine::StateMachine() {
    m_startingState = "intro";
    m_currentState = NULL;
}

as::StateMachine::~StateMachine() {
    for ( unsigned int i=0; i<m_states.size(); i++ ){
        delete m_states.at( i );
    }
}

int as::StateMachine::init() {
    lua_State* l = lua->m_l;
    // We'll count how many errors we encounter during startup.
    int errorcount = 0;
    // Grab a list of folders/files at data/states
    std::vector<std::string> statelist = filesystem->getFiles( "data/states", false );
    // Loop through the list of files.
    for ( unsigned int i=0; i<statelist.size(); i++ ) {
        // Discard non-directories
        if ( !filesystem->isDirectory( statelist.at( i ) ) ) {
            continue;
        }
        // We should have a folder now.
        std::string folder = statelist.at( i );
        // Discard folders that don't contain an init.lua file.
        if ( !filesystem->exists( folder + "/init.lua" ) ) {
            continue;
        }
        // Delete the old STATE global.
        lua_newtable( l );
        lua_setglobal( l, "STATE" );
        if ( lua->doFile( folder + "/init.lua" ) ) {
            // Oh shit we failed to parse the state!
            // Delete the STATE global and continue
            lua_pushnil( l );
            lua_setglobal( l, "STATE" );
            // Then add one to the error count
            errorcount++;
            continue;
        }
        // We successfully parsed a state here
        // Parse the state name FIXME: might have parsing problems for OS's without / directory separators.
        std::string statename = folder.substr( folder.find_last_of( '/' ) + 1 );
        // Now create a reference for this object.
        lua_getglobal( l, "STATE" );
        int reference = luaL_ref( l, LUA_REGISTRYINDEX );
        as::State* state = new as::State( statename, reference );
        // Finally we have a valid state created, add it to the list.
        m_states.push_back( state );
    }
    setState( m_startingState );
    return errorcount;
}

void as::StateMachine::tick( sf::Time deltaTime ) {
    if ( !m_currentState ) {
        return;
    }
    m_currentState->tick( deltaTime, lua->m_l );
}

int as::StateMachine::setState( std::string name ) {
    // TODO: Make this use binary search
    for ( unsigned int i=0; i<m_states.size(); i++ ){
        if ( m_states.at( i )->m_name == name ) {
            if ( m_currentState ) {
                m_currentState->exit( lua->m_l );
            }
            m_currentState = m_states.at( i );
            m_currentState->init( lua->m_l );
            return 0;
        }
    }
    as::printf( "ERR Couldn't switch to state %, it doesn't exist!\n", name );
    return 1;
}
