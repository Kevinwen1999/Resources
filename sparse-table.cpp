#define MAX_N 1000	// adjust this value as needed
#define LOG_TWO_N 10	// 2^10 > 1000, adjust this value as needed
class RMQ {		// Range Minimum Query
private:
	int _A[MAX_N], SpT[MAX_N][LOG_TWO_N];
public:
	RMQ(int n, int A[]) 
	{
		// constructor as well as pre-processing routine
		for (int i = 0; i < n; i++) 
		{
			_A[i] = A[i];
			SpT[i][0] = i; // RMQ of sub array starting at index i + length 2^0=1
		}

		// the two nested loops below have overall time complexity = O(n log n)
		for (int j = 1; (1<<j) <= n; j++)	// for each j s.t. 2^j <= n, O(log n)
			for (int i = 0; i + (1<<j) - 1 < n; i++)
			// for each valid i, O(n)
			if (_A[SpT[i][j-1]] < _A[SpT[i+(1<<(j-1))][j-1]])
			SpT[i][j] = SpT[i][j-1];	// start at index i of length 2^(j-1)
			else	
			SpT[i][j] = SpT[i+(1<<(j-1))][j-1]; // start at index i+2^(j-1) of length 2^(j-1)
	}
	int query(int i, int j) {
		// this query is O(1)
		int k = (int)floor(log((double)j-i+1) / log(2.0));	// 2^k <= (j-i+1)
		if (_A[SpT[i][k]] <= _A[SpT[j-(1<<k)+1][k]]) 
			return SpT[i][k];
		else
			return SpT[j-(1<<k)+1][k];
	} 

};
