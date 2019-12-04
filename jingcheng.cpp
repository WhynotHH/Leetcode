#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX_name 10
#define length 5
typedef struct process_data{//�������Ϣ��
	char name[MAX_name];//������
	int arrive_time;//����ʱ��
	int serve_time;//����ʱ��
	int served_time;//�ѷ���ʱ��
	int finish_time;//���ʱ��
}process_data;
typedef struct process{//�����ÿ���ڵ�
	 process_data data;
	 process* next;
 }process;
 typedef struct list_data{//��������
	process* head_process;
	int list_length;
 }list_data;
//��������
void inti_list_process(list_data** p);//����ʼ�����ʼ��
void write_begin_process(list_data* list); //���ļ������ݶ���begin_lprocess����
void change_wite_process();//�Եȴ����н����޸�
void count_finish_time();//�������ʱ��
void show_finish_time();
void show_begin_message();
//�������time��ʼֵΪ0
	int time = 0;
//����ʱ��Ƭ = 4
	int slice = 1;
list_data* begin_lprocess;//����begin���� ���ÿ���ڵ����Ϣ
list_data* wait_lprocess;//�����ȴ����� ��ŵȴ����н��̵���Ϣ
list_data* finish_lprocess;//����������� �����ɽ��̵���Ϣ

int main(){
	//��begin��wait��finish�����ʼ��
	inti_list_process(&begin_lprocess);
	inti_list_process(&wait_lprocess);
	inti_list_process(&finish_lprocess);
	//��begin����д����̵���Ϣ
	write_begin_process(begin_lprocess);
	show_begin_message();
	count_finish_time();
	show_finish_time();
	system("pause");
}
void show_begin_message(){
	process* p = (begin_lprocess ->head_process)->next;
	while(p){
		printf("��������%s  ",(p ->data).name);
		printf("����ʱ�䣺%d  ",(p ->data).arrive_time);
		printf("����ʱ�䣺%d\n",(p ->data).serve_time);
		p = p ->next;		
	}
}
void inti_list_process(list_data** p){//�������ʼ��
	*p = (list_data*)malloc(sizeof(list_data));
	(*p) -> list_length = 0;
	(*p) -> head_process = (process*)malloc(sizeof(process));
	((*p) -> head_process)->next = NULL;
 };
void write_begin_process(list_data* list){//����ʼ����д�� ������Ϣ
	process* p = list -> head_process;
	FILE* pread = fopen("process_list.bin","rb");
	for(int i = 0;i < 5;i++){//���ļ������ݶ���begin_lprocess����
		p -> next = (process*)malloc(sizeof(process));
		fread(p -> next,sizeof(process),1,pread);
		list ->list_length++;//ÿ�����һ�����̣�begin����ĳ��ȼ�һ
		p = p ->next;
	}
	/*FILE* pwrite = fopen("process_list.bin","wb");
	for(int i = 0;i < length;i++){
		p -> next = (process*)malloc(sizeof(process));
		printf("������:\n");
		scanf("%s",&((p -> next) ->data).name);
		printf("����ʱ�䣺\n");
		scanf("%d",&((p -> next) ->data).arrive_time);
		printf("����ʱ�䣺\n");
		scanf("%d",&((p -> next) ->data).serve_time);
		((p -> next) ->data).finish_time = 0;
		((p -> next) ->data).served_time = 0;
		(p->next)->next = NULL;
		p = p->next;
		fwrite(p,sizeof(process),1,pwrite);
	}
	fclose(pwrite);*/
	begin_lprocess ->list_length = length;
	fclose(pread);
}
void change_wite_process(){//�ı��������
	process* pbegin = begin_lprocess ->head_process;
	process* pwait =  wait_lprocess->head_process;
	process* pfinish = finish_lprocess ->head_process;
	process* pnow = NULL;
	//����begin���в鿴���Ƿ��е�ǰʱ������ڴ�Ľ��̣������ý��� β�� ������������
	while(pbegin ->next){//����begin���� ��wait_lprocessΪ�ջ���Ϊ1��û�����⣩ 
		if( ( (pbegin ->next) ->data ).arrive_time <= time ){//����ý��̵����ڴ� 
			pnow = (pbegin ->next);
			pbegin ->next = pnow ->next;//���ý��̴�begin����ɾ��
			pnow ->next =NULL;
			while(pwait ->next){//��pwait -> next�� Ϊ�ս������ҵ��ȴ���������һ��Ԫ��
				pwait = pwait ->next;
			}
			pwait ->next = pnow; //���Ƶ�wait����β
			begin_lprocess ->list_length--;
			wait_lprocess ->list_length++;
		}else{//���pbegin ->next��ָ��Ľ���δ�����ڴ� ������һ������
			pbegin = pbegin ->next;
		}
	}
	pwait =  wait_lprocess->head_process;
	//�������������û�н��� return
	if((pwait ->next) == NULL){
		return ;
	}else{
		//�鿴��������ĵ�һ�����̣������һ�������Ѿ�ִ����ɣ�
		//��1�����ý��̴Ӿ�������ɾ��
		//��2�����ý���β�嵽�������
		//��3���Ըý��̵����ʱ�丳ֵ
		//���û��ִ���꣺ ���ý��̴Ӿ�������ı�ͷ�嵽��β
		if(( (pwait ->next) ->data ).served_time == ((pwait ->next) ->data ).serve_time){//��һ�������Ѿ����
			pnow = pwait ->next;//��¼��һ�����̵ĵ�ַ��pnow
			pwait ->next = pnow ->next;//��1����pnow�ӵȴ�������ɾ����
			pnow ->next = NULL;
			while(pfinish ->next){//��pfinish -> next�� Ϊ�ս���:�ҵ�����������һ��Ԫ��
				pfinish = pfinish ->next;
			}
			pfinish ->next = pnow;//��2����pnowβ�嵽 �������
			(pnow ->data).finish_time = time;//��3���Խ��̵����ʱ����и�ֵ
			wait_lprocess->list_length--;
			finish_lprocess->list_length++;
		}else{// �ȴ������н��̣��ҵ�һ������û�����
			
			//�����������һ�����̷��������ĩβ
			pnow = pwait ->next;
			pwait ->next =  pnow ->next;
			pnow ->next =NULL;
			while(pwait ->next){
				pwait = pwait ->next;
			}
			pwait ->next =pnow;	
		}
	}
}
void count_finish_time(){
	while(finish_lprocess ->list_length < length){//�������ĳ��� С�� ���̵Ķ���cpu����ִ��
		change_wite_process();
		process* p = (wait_lprocess ->head_process)->next; //cpuִ�о������е�һ������
		if(p == NULL){//֤���ڴ�(�ȴ�����)û����ҵ
			time++;
		}else{//(�ȴ������ڴ棩����ҵ)
			int i = 0;
			while(((p ->data).served_time < (p ->data).serve_time) && (i < slice)){
				(p ->data).served_time++;
				time++;
				i++;
			}
		}
	}
}
//finish_time�ĸı�
void show_finish_time(){
	process* p = (finish_lprocess ->head_process) -> next;
	while(p){
		
		printf("����%s�����ʱ��:%d \n",(p -> data.name),(p -> data.finish_time) );
		p = p -> next;
	}
}