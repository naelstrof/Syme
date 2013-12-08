-- Intro state

function STATE:onInit()
    print( "State init!")
    self.sprite = AnimatedSprite( "t_foob" )
    self.sprite:setPos( Vector( 100, 100 ) )
end

function STATE:onExit()
    print( "State exit!")
    self.sprite:remove()
end

function STATE:onTick( dt )
    print( "State ticking by ", dt:asSeconds() )
    Scene.tick( dt )
end
