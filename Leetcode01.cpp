#include<stdio.h>
#include<stdlib.h>
int compare (const void * a, const void * b)//ϵͳ��qsort��Ҫ�õ��������
{
  return ( *(int*)a - *(int*)b );
}
//��������twosum ����ֵΪ:һ�������±�(���� int*)������nums �������鳤��length����Ŀ����target 
int* twosum(int* nums,int length,int target){
	
	//��Ϊ����Ҫ�󷵻ص���һ�����֣�����Ӧ��mollocһ������Ϊ2������result 
	int* result = (int*)malloc(sizeof(int)*2);//����ֵ
	
	//��malloc�µ�����newnums���ڱ���ԭ�����������˳��
	int *newnums = (int*)malloc(sizeof(int)*length);
	for(int  i = 0;i < length;i++){//��������
		newnums[i] = nums[i];
	}
	
	//�Դ���������������(�����Ӱ��ԭ�������˳��)
	qsort(newnums,length,sizeof(int),compare);//��������
	//�������� low=0��high=length-1�ֱ�����������������λ�͵�λ���±�
	int low = 0;
	int high = length - 1;
	//��whileѭ��(����Ϊlow<high)���low��high��Ӧ��ֵ��Ӵ���target(high--)���С��(low++)����������� 
	while(low < high){
		if(newnums[low] + newnums[high] < target){
			low++;
		} else if(newnums[low] + newnums[high] > target){
			high--;
		}else{
			break;
		}
	}
	
	if(low < high){//�ҵ��˶�Ӧ���������ض���
		//��newnums[low]��high]��Ӧ��ֵ������result[2]; 
		result[0] = newnums[low];
		result[1] = newnums[high];
		//free(newnums);
		free(newnums);
		//����result
		return result;
	}else{
		//free(newnums);
		free(newnums);
		return NULL;
	}
}
int main(){
	//����һ���������У��ҳ����к�Ϊ�ض�ֵ����������������Լ���ÿ�����붼ֻ����һ�ִ𰸣�ͬ����Ԫ�ز��ܱ�����
	//���� nums = [2, 7, 11, 15], target = 9��Ϊ nums[0] + nums[1] = 2 + 7 = 9���Է��� [0, 1]
	//˫ָ�뷨���
	
	//��������nums ��������
	int nums[]={2,7,11,15,6,5};
	//��������ĳ���length
	int length = sizeof(nums)/sizeof(int);
	//�ض�ֵtarget
	int target = 18;
	//����һ����������twosum�ķ���ֵ
	int* result = twosum(nums,length,target);
	
	if(result != NULL){
		//���������Ӧ��ֵ
		printf("������Ӧ��ֵΪ%d,%d\n",result[0],result[1]);
		//free(result);
		free(result);
	}else{
	//˵��δ�ҵ�
	printf("δ�ҵ���Ӧ��ֵ\n");
	//free(result);
	free(result);
	}
	system("pause");
	return 0;
}