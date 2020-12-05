#include <iostream>
#include "Storage.h"

void drawManager(Camera* camera, Storage* storage, float dt)
{
    Iterator iter(storage);
	while (true)
	{
		GameObject& gameObject = iter.stepIteration();
        if (gameObject.name == "NULL")
        { 
            break;
        }
        gameObject.draw(camera);   
        gameObject.animation(dt);     
    }

}

// void animationManager(float dt, Storage* storage)
// {
//     Iterator iter(storage);
// 	while (true)
// 	{
// 		GameObject& gameObject = iter.stepIteration();
//         if (gameObject.name == "NULL")
//         { 
//             break;
//         }
//         gameObject.animation(dt);        
//     }
// }