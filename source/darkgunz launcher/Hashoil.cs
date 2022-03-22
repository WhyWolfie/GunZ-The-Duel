using System.Security.Cryptography;
using System.Text;

public class Hashoil
{
	private static HashAlgorithm Alg;

	public static string Hash(string input)
	{
		using (MD5 md5Hash = MD5.Create())
		{
			return GetMd5Hash(md5Hash, input);
		}
	}

	private static string GetMd5Hash(MD5 md5Hash, string input)
	{
		byte[] array = md5Hash.ComputeHash(Encoding.UTF8.GetBytes(input));
		StringBuilder stringBuilder = new StringBuilder();
		for (int i = 0; i < array.Length; i++)
		{
			stringBuilder.Append(array[i].ToString("x2"));
		}
		return stringBuilder.ToString();
	}
}
