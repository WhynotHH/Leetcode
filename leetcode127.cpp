class Solution {
public:
	void do_of_word(string first_word_que, queue<string>& que, set<string>& wordset){
		//ö��first_word_que��ص����е���(word)��
		for (size_t i = 0; i < first_word_que.size(); i++){
			//ö��ÿ����ĸ������a - z���������
			string tem = first_word_que;
			char c = 'a';
			while (c <= 'z'){
				tem[i] = c;
				//a - z ��ÿ������� wordset�в������������: �õ��������,��wordset��ɾ�� 
				if (wordset.find(tem) != wordset.end()){
					wordset.erase(tem);//ɾ��
					que.push(tem);//����
				}
				//������ �����κβ���
				c++;
			};
		}
	}
	int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
		//����һ��set�洢wordlist�е����ݣ����ڲ��ҡ�
		set<string> wordset;
		for (auto &word : wordList){
			wordset.insert(word);
		}
		//�����������У���ʼֵ��beginword �� ���й����������
		queue<string> que;
		que.push(beginWord);
		int step = 1;//��¼����
		while (!que.empty()){
			//ÿ�������иò������ȫ�� ����������������һ
			int size = (int)que.size();
			while (size--){
				//�������Ϊ�գ� ˵������������·�����Է���0
				//���� ��¼���еĵ�һ������(front)������front���ӡ�
				if (que.empty()){
					return 0;
				}
				string first_word_que = que.front();
				que.pop();

				//���first_word_que����endword�� ����step��
				if (first_word_que == endWord){
					return step;
				}
				else{
					//�����first_word_que������Ӧ�Ĳ�����
					do_of_word(first_word_que, que, wordset);
				}
			}
			step++;
		}
		return 0;
	}
};