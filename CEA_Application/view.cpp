/**
  * @file view.cpp
  * @brief Implementation of the class View
  * @date December 2014
  * @author INSA, Elaine Dauchart and Dominik Wielgos
  */

#include "view.h"

View::View()
{
    cout << "new view" << endl;
}


/**
 * @brief View::displayLanes
 * @param select
 * Display the lanes on the current frame if the corresponding option is selected
 */
void View::displayLanes(bool select)
{
    if(select)
    {
        // call the corresponding function from Scene
        cvtColor(currentFrame,currentFrame,COLOR_BGR2RGB); // Temporary, to test the function call
    }
}
