class Solution {
public:
	void do_of_word(string first_word_que, queue<string>& que, set<string>& wordset){
		//枚举first_word_que相关的所有单词(word)。
		for (size_t i = 0; i < first_word_que.size(); i++){
			//枚举每个字母都换成a - z的所有情况
			string tem = first_word_que;
			char c = 'a';
			while (c <= 'z'){
				tem[i] = c;
				//a - z 的每种情况在 wordset中查找如果存在则: 该单词入队列,从wordset中删除 
				if (wordset.find(tem) != wordset.end()){
					wordset.erase(tem);//删除
					que.push(tem);//出队
				}
				//不存在 则不做任何操作
				c++;
			};
		}
	}
	int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
		//先用一个set存储wordlist中的内容，便于查找。
		set<string> wordset;
		for (auto &word : wordList){
			wordset.insert(word);
		}
		//借助辅助队列（初始值是beginword ） 进行广度优先搜索
		queue<string> que;
		que.push(beginWord);
		int step = 1;//记录步数
		while (!que.empty()){
			//每步将队列该层的数据全部 “操作”，步数加一
			int size = (int)que.size();
			while (size--){
				//如果队列为空： 说明不存在这条路。所以返回0
				//否则： 记录队列的第一个单词(front)，并且front出队。
				if (que.empty()){
					return 0;
				}
				string first_word_que = que.front();
				que.pop();

				//如果first_word_que等于endword： 返回step。
				if (first_word_que == endWord){
					return step;
				}
				else{
					//否则对first_word_que进行相应的操作。
					do_of_word(first_word_que, que, wordset);
				}
			}
			step++;
		}
		return 0;
	}
};