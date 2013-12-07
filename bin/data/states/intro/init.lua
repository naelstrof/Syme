-- Intro state

function STATE:onInit()
    print( "State init!")
end

function STATE:onExit()
    print( "State exit!")
end

function STATE:onTick( dt )
    print( "State ticking by ", dt )
end
