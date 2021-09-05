// TestProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../CommonUtilities/InputMapper.h"
#include "../CommonUtilities/XInputWrapper.h"
#include <chrono>
#include <thread>

int main()
{
    Input::InputMapper::Create();
    Input::XInputWrapper input;


    std::cout << input.ControllerIsConnected(0) << std::endl;


    unsigned short v = 0;
    while (true)
    {
        input.Update();
        if (input.GetButtonDown(Input::eControllerButtons::))


    }
}
