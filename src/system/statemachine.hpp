#ifndef AS_SYSTEM_STATEMACHINE_H_
#define AS_SYSTEM_STATEMACHINE_H_

#include <vector>
#include <string>
#include <SFML/System/Time.hpp>

#include "state.hpp"
#include "print.hpp"

namespace as {

class State;

class StateMachine {
public:
                            StateMachine();
                            ~StateMachine();
    void                    tick( sf::Time deltaTime );
    int                     init();
    int                     setState( std::string name );

    as::State*              m_currentState;
    std::vector<as::State*> m_states;
    std::string             m_startingState;
};

};

extern as::StateMachine* statemachine;

#endif // AS_SYSTEM_STATEMACHINE_H_
