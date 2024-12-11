using System;
using System.Buffers;
using System.Diagnostics;
using System.Numerics;
using System.Runtime;

class Program
{
	static void Main(string[] args)
	{
		string inputFile;
		if (args.Length == 0)
		{
			inputFile = "../../../i1";
		}
		else
		{
			inputFile = args[0];
		}

		if (!File.Exists(inputFile))
		{
			Console.WriteLine($"File not found: {inputFile}");
		}

		string fileContents = File.ReadAllText(inputFile).Trim();
		List<long> ids = new List<long>();

		/* NOTE(pf): ID can be > 9, so we need to ensure that we capture the
			correct number of repeats and also store this information for the next process.
		*/

		int i, j;
		int dbgHits = 0, dbgMiss = 0;
		for (i = 0; i < fileContents.Length; ++i)
		{
			int repeats;
			char c = fileContents[i];
			Debug.Assert(c >= '0' && c <= '9');
			repeats = c - '0';
			Debug.Assert(repeats >= 0 && repeats < 10);
			int val = -1;
			if ((i % 2) == 0)
			{
				val = i / 2;
			}
			for (j = 0; j < repeats; ++j)
			{
				ids.Add(val);

				if ((i % 2) == 0)
				{
					++dbgHits;
				}
				else
				{
					++dbgMiss;
				}
			}
		}

        long result = 0;
		i = 0;
		j = ids.Count - 1;
		while(i < j) {
			while(i < j && ids[i] != -1) {
				++i;
			}
			while(i < j && ids[j] == -1)
				--j;
			
			ids[i] = ids[j];
			ids[j] = -1;
			++i;
			--j;
		}

		for(i = 0; i < j; ++i) {
			long part = (long)((long)ids[i] * (long)i);
			Debug.Assert(part >= ids[i]);
			result += part;
		}

		// for (i = 0, j = ids.Count - 1; i <= j; ++i)
		// {
		// 	BigInteger partSum = ids[i];
		// 	if (ids[i] == -1)
		// 	{
		// 		while (partSum < 0 && i < j)
		// 			partSum = ids[j--];
		// 		if (i >= j)
		// 			break;
		// 	}

		// 	// sanityCheck.Add(((int)partSum));

		// 	Debug.Assert(partSum >= 0);
		// 	Debug.Assert((partSum * i) >= 0);
		// 	Debug.Assert((partSum * i) >= partSum);
		// 	Debug.Assert((result + (partSum * i)) >= result);
		// 	result += partSum * i;
		// }
		// result = 0;
		// for(i = 0; i < sanityCheck.Count; ++i)
		// 	result += i * sanityCheck[i];

		Console.WriteLine(result);
	}
}