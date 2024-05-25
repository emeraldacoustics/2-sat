#include <vector>

using namespace std;

class TwoSAT
{
public:
	static const int maxn = 1000;

	int n;
	vector<int> E[maxn * 2];
	int c;
	int s[maxn];

	bool mark[maxn * 2];

	TwoSAT(void) : n(0)
	{

	}

	void resize(const int & n)
	{
		for (int i = 0; i < this->n * 2; i++)
			E[i].clear();
		this->n = n;
	}

	void add_clause(const int & u, const bool & uval, const int & v, const bool & vval)
	{
		E[u * 2 + !uval].push_back(v * 2 + vval);
		E[v * 2 + !vval].push_back(u * 2 + uval);
	}

	bool dfs(const int & u)
	{
		if (mark[u ^ 1])
			return false;
		else if (mark[u])
			return true;
		else
		{
			mark[u] = true;
			s[c++] = u;
			for (const auto & v : E[u])
			{
				if (!dfs(v))
					return false;
			}
			return true;
		}
	}

	bool solve(void)
	{
		memset(mark, false, sizeof mark[0] * this->n * 2);
		for (int i = 0; i < n * 2; i += 2)
		{
			if (!mark[i] && !mark[i ^ 1])
			{
				c = 0;
				if (!dfs(i))
				{
					for(; c > 0; )
						mark[s[--c]] = false;
					if(!dfs(i ^ 1))
						return false;
				}
			}
		}
		return true;
	}
};
