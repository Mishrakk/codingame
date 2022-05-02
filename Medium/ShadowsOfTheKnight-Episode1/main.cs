using System;
class Player
{
    static void Main(string[] args)
    {
        string[] inputs;
        inputs = Console.ReadLine().Split(' ');
        int width = int.Parse(inputs[0]);
        int height = int.Parse(inputs[1]);
        int maxRounds = int.Parse(Console.ReadLine());
        inputs = Console.ReadLine().Split(' ');
        int batmanX = int.Parse(inputs[0]);
        int batmanY = int.Parse(inputs[1]);

        int minX = 0;
        int minY = 0;
        int maxX = width - 1;
        int maxY = height - 1;

        while (true)
        {
            string bombDirection = Console.ReadLine();

            if (bombDirection.Contains("U"))
                maxY = batmanY - 1;

            if (bombDirection.Contains("D"))
                minY = batmanY + 1;

            if (bombDirection.Contains("L"))
                maxX = batmanX - 1;

            if (bombDirection.Contains("R"))
                minX = batmanX + 1;

            batmanX = (maxX + minX) / 2;
            batmanY = (maxY + minY) / 2;


            Console.WriteLine("{0} {1}", batmanX, batmanY);
        }
    }
}