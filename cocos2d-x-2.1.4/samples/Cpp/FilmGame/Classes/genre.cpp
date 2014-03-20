//
//  genre.cpp
//  FilmGame
//
//  Created by Anthony Jones on 11/3/13.
//
//

#include "genre.h"

genre::genre(GenresEnum g){
    m_genre = g;
    
    switch (g) {
        case action:
            post = 1.5;
            pre = 0;
            ge = 0;
            cast = 0.7;
            camera = 1.1;
            sound = 0;
            art = 0;
            break;
            
        case adventure:
            post = 0;
            pre = 0;
            ge = 1.7;
            cast = 0.8;
            camera = 1.1;
            sound = 0.8;
            art = 0;
            break;
        case comedy:
            post = 1;
            pre = 1;
            ge = 1;
            cast = 2.0;
            camera = 1;
            sound = 1;
            art = 1;
            break;
        case children:
            post = 1.2;
            pre = 1.2;
            ge = 1.2;
            cast = 1.2;
            camera = 1.2;
            sound = 1.2;
            art = 1.2;
            break;
        case romance:
            post = 0.0;
            pre = 0;
            ge = 0;
            cast = 1.8;
            camera = 0.8;
            sound = 0.7;
            art = 0;
            break;
        case thriller:
            post = 0.0;
            pre = 0;
            ge = 0;
            cast = 1.1;
            camera = 0.8;
            sound = 1.4;
            art = 0;
            break;
        case horror:
            post = 0;
            pre = 0;
            ge = 0.8;
            cast = 0;
            camera = 0.8;
            sound = 1.8;
            art = 0;
            break;
        case heist:
            post = 0;
            pre = 0.6;
            ge = 1.6;
            cast = 0;
            camera = 1.1;
            sound = 0;
            art = 0;
            break;
        case period:
            post = 0;
            pre = 0.9;
            ge = 0.8;
            cast = 0;
            camera = 0;
            sound = 0;
            art = 1.6;
            break;
        case indie:
            post = 1.3;
            pre = 1.3;
            ge = 1.3;
            cast = 1.3;
            camera = 1.3;
            sound = 1.3;
            art = 1.3;
            break;
        case cerebral:
            post = 0.9;
            pre = 2.0;
            ge = 0.9;
            cast = 0.9;
            camera = 0.9;
            sound = 0.9;
            art = 0.9;
            break;
        case documentary:
            post = 0;
            pre = 1.8;
            ge = 0;
            cast = 0;
            camera = 0.8;
            sound = 0;
            art = 0.6;
            break;
        case fantasty:
            post = 1.1;
            pre = 0;
            ge = 0;
            cast = 0.8;
            camera = 0;
            sound = 0;
            art = 1.7;
            break;
        case scifi:
            post = 1.7;
            pre = 0;
            ge = 1.1;
            cast = 0.8;
            camera = 0;
            sound = 0;
            art = 0;
            break;
        case experimental:
            post = 1;
            pre = 1;
            ge = 1;
            cast = 1;
            camera = 1.6;
            sound = 0.7;
            art = 1;
            break;

        default:
            break;
    }
    
}
