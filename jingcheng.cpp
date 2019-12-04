#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX_name 10
#define length 5
typedef struct process_data{//链表的信息区
	char name[MAX_name];//进程名
	int arrive_time;//到达时间
	int serve_time;//服务时间
	int served_time;//已服务时间
	int finish_time;//完成时间
}process_data;
typedef struct process{//链表的每个节点
	 process_data data;
	 process* next;
 }process;
 typedef struct list_data{//整个链表
	process* head_process;
	int list_length;
 }list_data;
//函数声明
void inti_list_process(list_data** p);//给开始链表初始化
void write_begin_process(list_data* list); //将文件的内容读入begin_lprocess链表
void change_wite_process();//对等待队列进行修改
void count_finish_time();//计算完成时间
void show_finish_time();
void show_begin_message();
//定义变量time初始值为0
	int time = 0;
//定义时间片 = 4
	int slice = 1;
list_data* begin_lprocess;//创建begin链表 存放每个节点的信息
list_data* wait_lprocess;//创建等待链表 存放等待队列进程的信息
list_data* finish_lprocess;//创建完成链表 存放完成进程的信息

int main(){
	//给begin，wait，finish链表初始化
	inti_list_process(&begin_lprocess);
	inti_list_process(&wait_lprocess);
	inti_list_process(&finish_lprocess);
	//给begin链表写入进程的信息
	write_begin_process(begin_lprocess);
	show_begin_message();
	count_finish_time();
	show_finish_time();
	system("pause");
}
void show_begin_message(){
	process* p = (begin_lprocess ->head_process)->next;
	while(p){
		printf("进程名：%s  ",(p ->data).name);
		printf("到达时间：%d  ",(p ->data).arrive_time);
		printf("服务时间：%d\n",(p ->data).serve_time);
		p = p ->next;		
	}
}
void inti_list_process(list_data** p){//给链表初始化
	*p = (list_data*)malloc(sizeof(list_data));
	(*p) -> list_length = 0;
	(*p) -> head_process = (process*)malloc(sizeof(process));
	((*p) -> head_process)->next = NULL;
 };
void write_begin_process(list_data* list){//给开始链表写入 进程信息
	process* p = list -> head_process;
	FILE* pread = fopen("process_list.bin","rb");
	for(int i = 0;i < 5;i++){//将文件的内容读入begin_lprocess链表
		p -> next = (process*)malloc(sizeof(process));
		fread(p -> next,sizeof(process),1,pread);
		list ->list_length++;//每次添加一个进程，begin链表的长度加一
		p = p ->next;
	}
	/*FILE* pwrite = fopen("process_list.bin","wb");
	for(int i = 0;i < length;i++){
		p -> next = (process*)malloc(sizeof(process));
		printf("进程名:\n");
		scanf("%s",&((p -> next) ->data).name);
		printf("到达时间：\n");
		scanf("%d",&((p -> next) ->data).arrive_time);
		printf("服务时间：\n");
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
void change_wite_process(){//改变就绪队列
	process* pbegin = begin_lprocess ->head_process;
	process* pwait =  wait_lprocess->head_process;
	process* pfinish = finish_lprocess ->head_process;
	process* pnow = NULL;
	//遍历begin对列查看：是否有当前时间进入内存的进程，并将该进程 尾插 到就绪链表中
	while(pbegin ->next){//遍历begin链表 （wait_lprocess为空或者为1都没有问题） 
		if( ( (pbegin ->next) ->data ).arrive_time <= time ){//如果该进程到达内存 
			pnow = (pbegin ->next);
			pbegin ->next = pnow ->next;//将该进程从begin链表删除
			pnow ->next =NULL;
			while(pwait ->next){//（pwait -> next） 为空结束：找到等待链表的最后一个元素
				pwait = pwait ->next;
			}
			pwait ->next = pnow; //并移到wait链表尾
			begin_lprocess ->list_length--;
			wait_lprocess ->list_length++;
		}else{//如果pbegin ->next所指向的进程未到达内存 则检查下一个进程
			pbegin = pbegin ->next;
		}
	}
	pwait =  wait_lprocess->head_process;
	//如果就绪链表中没有进程 return
	if((pwait ->next) == NULL){
		return ;
	}else{
		//查看就绪链表的第一个进程，如果第一个进程已经执行完成：
		//（1）将该进程从就绪链表删除
		//（2）将该进程尾插到完成链表
		//（3）对该进程的完成时间赋值
		//如果没有执行完： 将该进程从就绪链表的表头插到表尾
		if(( (pwait ->next) ->data ).served_time == ((pwait ->next) ->data ).serve_time){//第一个进程已经完成
			pnow = pwait ->next;//记录第一个进程的地址到pnow
			pwait ->next = pnow ->next;//（1）将pnow从等待链表中删除；
			pnow ->next = NULL;
			while(pfinish ->next){//（pfinish -> next） 为空结束:找到完成链表的下一个元素
				pfinish = pfinish ->next;
			}
			pfinish ->next = pnow;//（2）将pnow尾插到 完成链表
			(pnow ->data).finish_time = time;//（3）对进程的完成时间进行赋值
			wait_lprocess->list_length--;
			finish_lprocess->list_length++;
		}else{// 等待链表有进程，且第一个进程没有完成
			
			//将就绪链表第一个进程放在链表得末尾
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
	while(finish_lprocess ->list_length < length){//完成链表的长度 小于 进程的多少cpu继续执行
		change_wite_process();
		process* p = (wait_lprocess ->head_process)->next; //cpu执行就绪队列第一个进程
		if(p == NULL){//证明内存(等待链表)没有作业
			time++;
		}else{//(等待链表（内存）有作业)
			int i = 0;
			while(((p ->data).served_time < (p ->data).serve_time) && (i < slice)){
				(p ->data).served_time++;
				time++;
				i++;
			}
		}
	}
}
//finish_time的改变
void show_finish_time(){
	process* p = (finish_lprocess ->head_process) -> next;
	while(p){
		
		printf("进程%s的完成时间:%d \n",(p -> data.name),(p -> data.finish_time) );
		p = p -> next;
	}
}