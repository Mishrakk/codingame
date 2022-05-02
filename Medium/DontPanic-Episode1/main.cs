using System;
using System.Linq;
using System.IO;
using System.Text;
using System.Collections;
using System.Collections.Generic;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
class Player
{
    static void Main(string[] args)
    {
        string[] inputs;
        inputs = Console.ReadLine().Split(' ');
        int nbFloors = int.Parse(inputs[0]); // number of floors
        
        int width = int.Parse(inputs[1]); // width of the area
        int nbRounds = int.Parse(inputs[2]); // maximum number of rounds
        int exitFloor = int.Parse(inputs[3]); // floor on which the exit is found
        int exitPos = int.Parse(inputs[4]); // position of the exit on its floor
        int nbTotalClones = int.Parse(inputs[5]); // number of generated clones
        int nbAdditionalElevators = int.Parse(inputs[6]); // ignore (always zero)
        int nbElevators = int.Parse(inputs[7]); // number of elevators
        int[] exitLocationOnFloor = new int[nbFloors];
        for (int i = 0; i < nbElevators; i++)
        {
            inputs = Console.ReadLine().Split(' ');
            int elevatorFloor = int.Parse(inputs[0]); // floor on which this elevator is found
            int elevatorPos = int.Parse(inputs[1]); // position of the elevator on its floor
            exitLocationOnFloor[elevatorFloor] = elevatorPos;
        }
        exitLocationOnFloor[exitFloor] = exitPos;

        // game loop
        while (true)
        {
            inputs = Console.ReadLine().Split(' ');
            int cloneFloor = int.Parse(inputs[0]); // floor of the leading clone
            int clonePos = int.Parse(inputs[1]); // position of the leading clone on its floor
            string direction = inputs[2]; // direction of the leading clone: LEFT or RIGHT
            // Write an action using Console.WriteLine()
            // To debug: Console.Error.WriteLine("Debug messages...");
            if(cloneFloor == -1 || IsCloneGoingInDirectionOfExit(direction, clonePos, exitLocationOnFloor[cloneFloor]) ){
                Console.WriteLine("WAIT");
            } else {
                Console.WriteLine("BLOCK");
            }
        }
    }
    public static bool IsCloneGoingInDirectionOfExit(string cloneDirection, int clonePosition, int exitPosition){
        if (cloneDirection == ExitDirection(clonePosition, exitPosition) || clonePosition == exitPosition){
            return true;
        } else {
            return false;
        }
    }
    public static string ExitDirection(int clonePosition, int exitPosition){
        if (exitPosition > clonePosition){
            return "RIGHT";
        } else {
            return "LEFT";
        }
    }
}