using System;
using System.Collections.Generic;

class Solution
{
    static void Main(string[] args)
    {
        string[] inputs = Console.ReadLine().Split(' ');
        int width = int.Parse(inputs[0]);
        int height = int.Parse(inputs[1]);
        string imageString = Console.ReadLine();
        Image image = new Image(width, height, imageString);
        string[] notes = image.GetNotes();
        Console.WriteLine(string.Join(" ", notes));
    }
}

class Image
{
    private readonly int Width;
    private readonly int Height;
    private readonly bool[] ImageArray;
    private int BlackLineHeight;
    private readonly int[] BlackLinesStarts = new int[6];
    private int NoteHeight;
    private readonly int UpperWhiteOffset;
    public Image(int width, int height, string image)
    {
        ImageArray = new bool[(width + 1) * (height + 1)];
        Width = width;
        Height = height;
        ParseImageToArray(image);
        GetBlackLineHeight();
        GetBlackLinesStartHeights();
        UpperWhiteOffset = BlackLinesStarts[0] - NoteHeight;
        //Console.Error.WriteLine("Note height: {0}, UpperWhiteOffset: {1}", NoteHeight, UpperWhiteOffset);
    }
    public string[] GetNotes()
    {
        List<string> notes = new List<string>();
        for (int x = 0; x < Width; x++)
        {
            string note = "";
            int noteY = 0;
            int noteMaxX = 0;
            for (int y = 0; y < Height; y++)
            {
                if (GetPixel(x,y) && IsNote(x, y))
                {
                    note = GetNote(y);
                    noteY = y;
                    break;
                }
            }
            if (noteY == 0)
            {
                continue;
            }
            for (int noteX = x; noteX < Width; noteX++)
            {
                bool blackPixelFound = false;
                for (int y = 0; y < Height; y++)
                {
                    if (GetPixel(noteX, y) && IsNote(noteX, y))
                    {
                        blackPixelFound = true;
                        break;
                    }
                }
                if (!blackPixelFound)
                {
                    noteMaxX = noteX -1;
                    int middlePixel = x + (noteMaxX - x) / 2;
                    //Console.Error.WriteLine("noteMaxX: {0}, x: {1}, noteY: {2}, mid: {3}", noteMaxX, x, noteY, middlePixel);
                    note += GetPixel(middlePixel, noteY) ? "Q" : "H";
                    break;
                } 
            }
            //Console.Error.WriteLine("Found note {0} at ({1}, {2})", note, x, noteY);
            notes.Add(note);
            x = noteMaxX;
        }
        return notes.ToArray();
    }
    private bool GetPixel(int x, int y)
    {
        return ImageArray[x + Width * y];
    }
    private bool IsNote(int x, int y)
    {
        foreach (int lineStart in BlackLinesStarts)
        {
            if (y >= lineStart && y < lineStart + BlackLineHeight)
            {
                return false;
            }
        }
        return true;
    }
    private void ParseImageToArray(string image)
    {
        string[] imageParts = image.Split(' ');
        int position = 0;
        for (int i = 0; i < imageParts.Length; i += 2)
        {
            string color = imageParts[i];
            int pixels = int.Parse(imageParts[i + 1]);
            for (int j = 0; j < pixels; j++)
            {
                ImageArray[position++] = color == "W" ? false : true;
            }
        }
    }
    private void GetBlackLineHeight()
    {
        for (int x = 0; x < Width; x++)
        {
            int blackPixels = 0;
            for (int y = 0; y < Height; y++)
            {
                if (GetPixel(x, y))
                {
                    blackPixels++;
                }
            }
            if (blackPixels > 0)
            {
                BlackLineHeight = blackPixels / 5;
               //Console.Error.WriteLine("black pixels: {1}, Black line height: {0}", BlackLineHeight, blackPixels);
                break;
            }
        }
    }
    private void GetBlackLinesStartHeights()
    {
        for (int x = 0; x < Width; x++)
        {
            int i = 0;
            for (int y = 0; y < Height; y++)
            {
                if (GetPixel(x, y))
                {
                    BlackLinesStarts[i++] = y;
                    y += BlackLineHeight;
                }
            }
            if (BlackLinesStarts[0] > 0)
            {
                NoteHeight = BlackLinesStarts[1] - BlackLinesStarts[0] - BlackLineHeight;
                BlackLinesStarts[5] = BlackLinesStarts[4] + NoteHeight + BlackLineHeight;
                break;
            }
        }
        Console.Error.WriteLine("Black lines starts: {0}", string.Join(", ", BlackLinesStarts));
    }
    private string GetNote2(int pixelHeight)
    {
        int halfNoteHeight = NoteHeight / 2;   
        string note = "";
        if (pixelHeight < BlackLinesStarts[0] - halfNoteHeight)
        {
            note = "G";
        }
        else if (pixelHeight < BlackLinesStarts[0] && pixelHeight > BlackLinesStarts[0] - halfNoteHeight)
        {
            note = "F";
        }
        else if (pixelHeight < BlackLinesStarts[1] - halfNoteHeight)
        {
            note = "E";
        }
        else if (pixelHeight < BlackLinesStarts[1] && pixelHeight > BlackLinesStarts[1] - halfNoteHeight)
        {
            note = "D";
        }
        else if (pixelHeight < BlackLinesStarts[2] - halfNoteHeight)
        {
            note = "C";
        }
        else if (pixelHeight < BlackLinesStarts[2] && pixelHeight > BlackLinesStarts[2] - halfNoteHeight)
        {
            note = "B";
        }
        else if (pixelHeight < BlackLinesStarts[3] - halfNoteHeight)
        {
            note = "A";
        }
        else if (pixelHeight < BlackLinesStarts[3] && pixelHeight > BlackLinesStarts[3] - halfNoteHeight)
        {
            note = "G";
        }
        else if (pixelHeight < BlackLinesStarts[4] - halfNoteHeight)
        {
            note = "F";
        }
        else if (pixelHeight < BlackLinesStarts[4] && pixelHeight > BlackLinesStarts[4] - halfNoteHeight)
        {
            note = "E";
        }
        else if (pixelHeight < BlackLinesStarts[5] - halfNoteHeight)
        {
            note = "D";
        }
        else if (pixelHeight < BlackLinesStarts[5] && pixelHeight > BlackLinesStarts[5] - halfNoteHeight)
        {
            note = "C";
        }
        Console.Error.WriteLine("pixelHeight: {0}, UpperWhiteOffset: {1}, NoteHeight: {2}", pixelHeight, UpperWhiteOffset, NoteHeight);
        int betterNoteY = (pixelHeight - UpperWhiteOffset + 1) / (halfNoteHeight+1);
        char note2 = (char)('G' - ((betterNoteY) % 7));
        Console.Error.WriteLine("better searching gives note: {0}, and betterNoteY: {1}, actuall note: {2}", note2, betterNoteY, note);
        //string note3 = GetNote2(pixelHeight);
        //Console.Error.WriteLine("Even better algorithm: {0}, actuall: {1}", note3, note);
        return note;
    }
    private string GetNote(int pixelHeight)
    {
        int halfNoteHeight = NoteHeight / 2;
        int zone = 0;
        for (int i = 0; i < 6; i++)
        {
            if (pixelHeight < BlackLinesStarts[i])
            {
                if (pixelHeight < BlackLinesStarts[i] - halfNoteHeight)
                {
                    zone = 2 * i;
                }
                else
                {
                    zone = 2 * i + 1;
                }
                break;
            }
        }
        char note2 = (char)('G' - ((zone) % 7));
        return note2.ToString();
    }
}