namespace Challenge7;

public class Program {
    public static void Main() {
        var client = new Client();

        var initialCell = client.currentPosition;

        var mapSize = 30;
        
        var map = new int[mapSize, mapSize];

        Point? exitCell = null;

        // Fill array with Unknown
        for (var x = 0; x < mapSize; x++) {
            for (var y = 0; y < mapSize; y++) {
                map[x, y] = -1;
            }
        }

        // Set of not walked cells
        var notWalked = new HashSet<Point>();

        notWalked.Add(client.currentPosition);

        while (notWalked.Count > 0) {
            var point = notWalked.First();
            notWalked.Remove(point);

            client.goTo(point);

            map[point.X, point.Y] = getSteps(map, point);

            if (client.isExit()) {
                exitCell = point;
            }

            foreach (var neighbor in client.look()) {
                if (map[neighbor.X, neighbor.Y] == -1) {
                    notWalked.Add(neighbor);
                }
            }
        }

        for (var x = 0; x < mapSize; x++) {
            for (var y = 0; y < mapSize; y++) {
                Console.Write(new Point{X = x, Y = y} == exitCell ? "X" : map[x, y] >= 0 ? " " : ".");
            }
            Console.WriteLine();
        }

        // Find shortest path from finalCell to initialCell
        var shortestPath = new List<Point>();
        var currentCell = exitCell.Value;
        while (currentCell != initialCell) {
            Console.WriteLine(currentCell);
            shortestPath.Add(currentCell);

            foreach (var neighbor in new Point[]{currentCell.North(), currentCell.South(), currentCell.East(), currentCell.West()}) {
                if (neighbor.X < 0 || neighbor.X >= map.GetLength(0) || neighbor.Y < 0 || neighbor.Y >= map.GetLength(1) || map[neighbor.X, neighbor.Y] == -1) {
                    continue;
                }

                if (map[neighbor.X, neighbor.Y] < map[currentCell.X, currentCell.Y]) {
                    currentCell = neighbor;
                    break;
                }
            };
        }

        shortestPath.Add(initialCell);
        shortestPath.Reverse();

        // Print all cells with the format (x, y),...
        Console.WriteLine(string.Join(", ", shortestPath));

    }

    private static int getSteps(int[,] map, Point point) {
        // Iterate direct neighbors and find the one with the lowest steps
        var minSteps = int.MaxValue;

        foreach (var neighbor in new Point[]{point.North(), point.South(), point.East(), point.West()}) {
            if (neighbor.X < 0 || neighbor.X >= map.GetLength(0) || neighbor.Y < 0 || neighbor.Y >= map.GetLength(1) || map[neighbor.X, neighbor.Y] == -1) {
                continue;
            }

            if (map[neighbor.X, neighbor.Y] < minSteps) {
                minSteps = map[neighbor.X, neighbor.Y];
            }
        };

        return minSteps + 1;
    }
}