#include<stdio.h>
#include<time.h>
#include <stdlib.h>
#include <string.h>
struct persondata
{
	int number;
	int counter;
	time_t intime;
	time_t time;
	int position;
	struct persondata*next;
};
int main()
{
	time_t t;//initial time
	time_t t1;//for checking if time reached
	int total;//total number of persons in queue
	FILE*fp;//file pointer
	int c;
	time(&t);//recording initial time
	fp=fopen("qmsdata.txt","r");
	fscanf(fp,"%d",&total);
	struct persondata*head;
	struct persondata*temp;
	struct persondata*tail;
	head=(struct persondata*)malloc(sizeof(struct persondata));//allocate space for head
	fscanf(fp,"%d",&head->number);
	fscanf(fp,"%ld",&head->time);
	head->counter=1;
	head->intime=1;
	tail=head;
	while(fscanf(fp,"%d",&c)!=EOF)
	{
		temp=(struct persondata*)malloc(sizeof(struct persondata));
		tail->next=temp;
		temp->number=c;
		fscanf(fp,"%ld",&temp->time);
		tail=temp;
	}//maintaining linked list
	struct persondata*temper;
	temper=head;
	if(total<=9)
	{
		int i=temper->number;
		while(temper!=NULL){
			printf("person %d enter counter %d\n",i,(i-1)%3+1);
			temper=temper->next;
			i++;
		}
	}//persons less than 9
	else //for greater than 9 persons
	{
		struct persondata*tem;
		tem = head;
		while(tem->number<=3)
		{
			tem->counter=tem->number;
			tem->position=1;
			tem = tem->next;
		}
		while(3<tem->number && tem->number<=6)
		{
			tem->counter=tem->number-3;
			tem->position=2;
			tem = tem->next;
		}
		while(6<tem->number&& tem->number<=9)
		{
			tem->counter=tem->number-6;
			tem->position=3;
			tem = tem->next;
		}//assigning positions

		struct persondata*temp1;
		temp1=head;
		while(temp1->number<=3)
		{
			temp1->intime=1;//initially entering
			temp1 = temp1->next;
		}
		while(3<temp1->number&& temp1->number<=9)
		{
			struct persondata* temp6;
			temp6=head;
			while(temp6!=NULL)
			{
				if(temp6->counter==temp1->counter)
				{
					if(temp6->position<temp1->position)
					{
						temp1->intime=1+temp6->time+temp1->intime;//for other persons who entered initially
					}
				}
				temp6=temp6->next;
			}
			temp1 = temp1->next;
		}

		int i=temper->number;
		while(i<=9){
			printf("person %d enter counter %d service will be started at at %ld and takes %ld seconds\n",i,(i-1)%3+1,temper->intime,temper->time);
			temper=temper->next;
			i++;
		}

		while(temp1!=NULL)
		{
			struct persondata*temp2;
			temp2=head;
			while (temp2!=NULL) {
				time(&t1);
				if(temp2->position==1)
				{
					if(t1 == t+temp2->time+temp2->intime)//time at which someone leaves
					{

						struct persondata*temp5;
						temp5=head;
						while(temp5!=NULL){
							if(temp5->counter==temp2->counter)
							{
								temp5->position=temp5->position-1;//updating position numbers
							}
							temp5 = temp5->next;
						}

						temp1->counter = temp2->counter;
						temp1->position = 3;
						struct persondata* temp7;
						temp7=head;
						while(temp7!=NULL)
						{
							if(temp7->counter==temp1->counter)
							{
								if(temp7->position<temp1->position)
								{
									temp1->intime=(t1-t)+temp7->time+temp7->intime;//for other persons who entered initially
								}
							}
							temp7=temp7->next;
						}
						printf("person %d enter counter %d service will be started at at %ld and takes %ld seconds\n",temp1->number,temp1->counter,temp1->intime,temp1->time);
						temp1 = temp1->next;
					}
				}
				temp2=temp2->next;//checking if it is other person intime
			}
		}
	}
	return 0;
}
