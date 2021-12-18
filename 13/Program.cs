using System.Net;
using System.Net.Http.Headers;
using System.Text;

namespace Challenge7;

public class Program
{
    public static async Task Main()
    {
        var client = new HttpClient(new HttpClientHandler() {
            MaxConnectionsPerServer = 20
        });

        // Generate all ascii chars
        var chars = new StringBuilder();
        for (int i = 0; i < 255; i++)
        {
            chars.Append((char)i);
        }

        var allChars = chars.ToString();

        Console.Error.WriteLine("Started");

        var responses = allChars
            .SelectMany(c1 => allChars.Select(c2 => (c1, c2)))
            .Select(async t => {
                while (true) {
                    try {
                        var request = new HttpRequestMessage(HttpMethod.Get, "http://codechallenge-daemons.0x14.net:13963");

                        request.Headers.Authorization =
                            new AuthenticationHeaderValue("Basic",Convert.ToBase64String(Encoding.UTF8.GetBytes($"plyba:xvyy{t.c1}nyy{t.c2}uhznaf")));
                            
                        var response = await client.SendAsync(request);
                        
                        Console.Error.WriteLine($"{(int)t.c1} {(int)t.c2}");

                        if (response.StatusCode != HttpStatusCode.Unauthorized || response.Content.Headers.GetValues("Content-Length").First() != "179")
                        {
                            Console.WriteLine($"plyba:xvyy{t.c1}nyy{t.c2}uhznaf");
                            Console.Error.WriteLine($"plyba:xvyy{t.c1}nyy{t.c2}uhznaf");
                        }

                        return (response, t);
                    } catch (Exception) {
                        Console.Error.WriteLine($"RETRY {(int)t.c1} {(int)t.c2}");
                    }
                }
            });

        await Task.WhenAll(responses);

        Console.Error.WriteLine("Finished");
    }
}