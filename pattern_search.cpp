
#include <iostream>
#include <vector>
using namespace std;


# define NO_OF_CHARS 256

void badCharHeuristic( string str, int size,
						int badchar[NO_OF_CHARS])
{
	int i;

	for (i = 0; i < NO_OF_CHARS; i++)
		badchar[i] = -1;

	for (i = 0; i < size; i++)
		badchar[(int) str[i]] = i;
}

vector<int> search( string txt, string pat)
{
    vector<int> indexes;
	int m = pat.size();
	int n = txt.size();

	int badchar[NO_OF_CHARS];

	badCharHeuristic(pat, m, badchar);

	int s = 0; 
	while(s <= (n - m))
	{
		int j = m - 1;

		
		while(j >= 0 && pat[j] == txt[s + j])
			j--;

		
		if (j < 0)
		{
            indexes.push_back(s);
			
			s += (s + m < n)? m-badchar[txt[s + m]] : 1;

		}

		else
			
			s += max(1, j - badchar[txt[s + j]]);
	}
	return indexes;
}






void solution(string g[], int row, int col, string patt) {
    
    
    //najpierw same rzedy
    for(int i = 0; i < row; i++){
        string w;
        for(int j = 0; j < col; j ++) {
            w += g[i][j];
        }
        
        //wszystkie indexy gdzie znajdowal sie pattern
        vector<int> idx = search(w, patt);
        
        
        
        if (!idx.empty()){
            
            for(int k = 0; k < idx.size(); k++){
                
                cout << " Pattern occured in horizontal search at  " << i << ", "<< idx[k]  << endl;
            }
        }
        
    }
    
    //kolumnami
    for(int i = 0; i < row; i++){
        string w;
        for(int j = 0; j < col; j ++) {
            w += g[j][i];
        }
        
        vector<int> idx = search(w, patt);
        if (!idx.empty()){
            
            for(int k = 0; k < idx.size(); k++){
                
                cout << " Pattern occured in vertical search at  " << i << ", "<< idx[k]  << endl;
            }
        }
        
    }
    //przekatne idac w gore pierwszej kolumny
    
    
    for(int i = row - 1; i >= 0; i--){
        string w;
        int p = i;
        int j = 0;
        while(p < row && j < col){
            w += g[p][j];
            p++;
            j++;
        }
        vector<int> idx = search(w, patt);
        
        
        if (!idx.empty()){
            
            for(int k = 0; k < idx.size(); k++){
                
                cout << " Pattern occured in diagonal by cols search at  " << i << ", "<< idx[k]  << endl;
            }
        }
        
    }
    
    
    //przekatne idac po pierwszym rzedzie
    for(int j = col - 1; j >= 0; j--){
        int c = j;
        string w;
        int i = 0;
        while(c < col && i < row ){
            w += g[i][c];
            c++;
            i++;
        }
        vector<int> idx = search(w, patt);
        
        if (!idx.empty()){
            
            for(int k = 0; k < idx.size(); k++){
                
                cout << " Pattern occured in diagonal by rows search at  " << j << ", "<< idx[k]  << endl;
            }
        }
        
    }
    
    
    
}


int main()
{
  string grid[4] = {"axmy",
                    "bgdf",
                    "xeet",
                    "raks"};
                    
    int row = 4;
    int col = 4;
    string patt = "ek";
    solution(grid,row,col,patt);
    return 0;
}
