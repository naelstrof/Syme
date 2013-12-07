local idle = Animation( "idle", 5, true,
                        IntRect( 0, 0, 32, 32 ),
                        IntRect( 32, 0, 32, 32 ) )

Resource.cacheSprite( "t_foob", "data/textures/foob.png", idle )
