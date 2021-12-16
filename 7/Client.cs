using System.Net.Sockets;

namespace Challenge7;

public class Client {
    private readonly TcpClient client;
    private readonly StreamReader reader;
    private readonly StreamWriter writer;

    public Point currentPosition { get; private set; }

    public Client() {
        client = new TcpClient("codechallenge-daemons.0x14.net", 4321);
        var stream = client.GetStream();

        reader = new(stream);
        writer = new(stream);

        writer.AutoFlush = true;
        writer.NewLine = "\n";

        readHeader();

        currentPosition = readCurrentPosition();
    }

    public string readLine() {
        var line = reader!.ReadLine()!;
        Console.WriteLine(line);
        return line;
    }

    public void writeLine(string line) {
        Console.WriteLine(">> " + line);
        writer!.WriteLine(line);
    }

    public void readHeader() {
        readLine();
        readLine();
    }

    public Point readCurrentPosition() {
        writeLine("where am I");

        var coordsStr = readLine();

        coordsStr = coordsStr.Remove(0, 1);
        coordsStr = coordsStr.Remove(coordsStr.IndexOf(')'), 1);
        
        var coords = coordsStr.Split(", ");

        return new Point {
            X = int.Parse(coords[0]),
            Y = int.Parse(coords[1])
        };
    }

    public bool goTo(Point point) {
        writeLine($"go to {point.X},{point.Y}");

        if (readLine().StartsWith("Great movement")) {
            currentPosition = point;
            return true;
        }

        return false;
    }

    public bool isExit() {
        writeLine("is exit?");
        return readLine() != "No. Sorry, traveller...";
    }

    public IEnumerable<Point> look() {
        writeLine("look");

        return readLine().Split(": ")[1].Split(" ")
            .Select(x => x switch {
                "north" => currentPosition.North(),
                "south" => currentPosition.South(),
                "east" => currentPosition.East(),
                "west" => currentPosition.West(),
                _ => throw new Exception("Unknown direction")
            });
    }
}