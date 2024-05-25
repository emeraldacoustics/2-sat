#include <vector>

using namespace std;

class TwoSAT
{
public:
	static const int maxn = 1000;

	int n;
	vector<vector<int> > e;
	int c;
	vector<int> s;
	vector<bool> mark;

	TwoSAT(void) : n(0)
	{

	}

	void resize(const int & n)
	{
		e.clear();
		e.resize(n << 1);
		this->n = n;
	}

	void add_clause(const int & u, const bool & uval, const int & v, const bool & vval)
	{
		e[u << 1 | !uval].push_back(v << 1 | vval);
		e[v << 1 | !vval].push_back(u << 1 | uval);
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
			for (const auto & v : e[u])
			{
				if (!dfs(v))
					return false;
			}
			return true;
		}
	}

	bool solve(void)
	{
		mark.clear();
		mark.resize(n << 1, false);
		for (int i = 0; i < n << 1; i += 2)
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
