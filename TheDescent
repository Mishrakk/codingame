using System;

class Player
{
    static void Main(string[] args)
    {
        // game loop
        while (true)
        {
            int indexOfHighestMountain = 0;
            int maximumHeight = 0;
            for (int currentMountainIndex = 0; currentMountainIndex < 8; currentMountainIndex++)
            {
                int currentMountainHeight = int.Parse(Console.ReadLine()); // represents the height of one mountain.
                if (currentMountainHeight > maximumHeight)
                {
                    maximumHeight = currentMountainHeight;
                    indexOfHighestMountain = currentMountainIndex;
                }
            }
            Console.WriteLine(indexOfHighestMountain);
        }
    }
}
