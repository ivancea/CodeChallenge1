namespace Challenge7;

public struct Point : IEquatable<Point>  {
    public int X { get; set; }
    public int Y { get; set; }

    public Point North() {
        return new Point { X = X, Y = Y + 1 };
    }

    public Point South() {
        return new Point { X = X, Y = Y - 1 };
    }

    public Point East() {
        return new Point { X = X - 1, Y = Y };
    }

    public Point West() {
        return new Point { X = X + 1, Y = Y };
    }

    public override bool Equals(object? obj) {
        return obj is Point point && Equals(point);
    }

    public bool Equals(Point point) {
        return X == point.X && Y == point.Y;
    }

    public override int GetHashCode() {
        return X ^ Y;
    }

    public override string ToString()
    {
        return $"({X}, {Y})";
    }

    public static bool operator==(Point pointA, Point pointB) {
        return pointA.Equals(pointB);
    }
    
    public static bool operator!=(Point pointA, Point pointB) {
        return !pointA.Equals(pointB);
    }
}