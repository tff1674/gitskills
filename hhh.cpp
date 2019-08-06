#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include<math.h>

using namespace std;

class Node//�����
{  public:
char oper;
Node *left;
Node *right;
int s;int t;
Node()
{   left=right=NULL;
    oper=0;
}  
Node(char op) {   left=right=NULL;
    oper=op;
}
};

bool isOper(char op)//�ж��Ƿ�Ϊ�����
{
char oper[]={'(',')','+','-','*','/','^'};
for(int i=0;i<sizeof(oper);i++)
{  if(op==oper[i])
   {
    return true;
   } 
}
return false;
}

int getOperOrder(char op)//���������op����Ӧ�����ȼ�
{
	switch(op){
	case '(': return 1;
    case '+': 
    case '-':return 2;
    case '*': 
    case '/':return 3;
    case '^':return 4;
    default:
	    return 0;   
	} 
}

void freeTree(Node *&p) //�ݹ�ɾ����
{ 
	if(p->left!=NULL)
       freeTree(p->left);
    if(p->right!=NULL)
       freeTree(p->right);
    delete(p); 
}

void postOrder(Node *p) //�������
{  if(p)
{  postOrder(p->left);
   postOrder(p->right);
   cout<<p->oper;
} 
}

void preOrder(Node *p) //�������
{  if(p)
{  cout<<p->oper;
   preOrder(p->left);
   preOrder(p->right);
} }

void inOrder(Node *p)//���������ͬʱ��������������ŵ���׺���ʽ
{  if(p)
{
	if(p->left)
   {//�����ǰ�ڵ���������������������������ȼ����ڵ�ǰ�������
		//��ô��ߵı��ʽҪ�ȼ��㣬��Ҫ������
		if(isOper(p->left->oper)&& getOperOrder(p->left->oper)<getOperOrder(p->oper))
    {  
			cout<<"(";
            inOrder(p->left);
            cout<<")";
    }
	else//����ֱ�����������
       inOrder(p->left);  
	}

   cout<<p->oper;//�����ǰ�ڵ�
   
   if(p->right)
   {  //�����ǰ�ڵ���������������������������ȼ������ڵ�ǰ�������
		//��ô�ұߵı��ʽҪ�ȼ��㣬��Ҫ������
	   if(isOper(p->right->oper)&& getOperOrder(p->right->oper)<=getOperOrder(p->oper))
    {  
		   cout<<"(";
     inOrder(p->right);
     cout<<")";
    }
	   else
     inOrder(p->right);
   }  
}  
}

void post2tree(Node *&p,string str)//��׺���ʽ���ɶ�����
{ stack <Node*> nodeStack;//���ڱ���ڵ�ָ���ջ
    char temp;
    int i=0;
    temp=str[i++];
   while(temp!='\0')
   {  
	   if(temp!='\0'&&!isOper(temp))//��������������ջ
    {  
		   p=new Node(temp);//��tempΪ���ֵ������������
           nodeStack.push(p);
           temp=str[i++];//������һ��
	 }
    else
	{  //����������ţ����ջ��������Ϊ�ҽڵ����ڵ�
		p=new Node(temp);
      if(nodeStack.size())
      {  
		  p->right=nodeStack.top();//���ǿ����ջ����Ϊ�����Һ���
       nodeStack.pop();  
	  }
      if(nodeStack.size())
      { 
		  p->left=nodeStack.top();//���ǿ����ջ����Ϊ��������
       nodeStack.pop();
	  }
      nodeStack.push(p);
	  temp=str[i++];
    } 
   } 
}


void pre2tree(Node *&p, string str)//ǰ׺���ʽ���ɶ�����
{
	stack <Node*> nodeStack;
 char temp;
 int i=str.size()-1;
  temp=str[i--];
 while(temp!='\0')
 {  
	 if(temp!='\0'&&!isOper(temp))
    {  p=new Node(temp);//��tempΪ�����������µĽ��
       nodeStack.push(p);
       temp=str[i--];}
    else
	{  p=new Node(temp);
	      if(nodeStack.size())//ջ�ǿ�
      {   p->left=nodeStack.top(); //��ջ��ָ����ָ������óɵ�ǰ�������
       nodeStack.pop();
      } 
	if(nodeStack.size())//ջ�ǿ�
	{  p->right=nodeStack.top();//��ջ��ָ����ָ������óɵ�ǰ����Һ���
       nodeStack.pop();//ջ��Ԫ�����Һ���ָ��������ϵ���
	}
     nodeStack.push(p);
	  temp=str[i--];
    }
 }
 }
void in2tree(Node *&p, string str)//��׺���ʽת���ɺ�׺���ʽ���ɶ�����
{  
	stack<char> a;
    char temp;
   string Postfixexp="";
   int i=0;
    temp=str[i++];
   while(temp!='\0')
   { 
	   if(!isOper(temp))//��������ֱ�ӽ�����ջ
	{  Postfixexp+=temp;
      temp=str[i++];
	}
       else if(temp=='(')//��ջ
	{
		   a.push(temp);
         temp=str[i++];
	 }
	 else if(temp==')')
	 {
	     while(a.top()!='(')//������
		 {
			 Postfixexp+=a.top();
		     a.pop();//�����������ź�ջΪ��ǰ��������ջ��Ԫ��
		 }
              a.pop();
			  temp=str[i++];
	 }
	else if(temp=='+'||temp=='-'||temp=='*'||temp=='/')//��ջ
	{
	while(!a.empty()&&a.top()!='('&&getOperOrder(a.top())>=getOperOrder(temp))
		//��ջ�ǿ�ջ��������������ջ��Ԫ�����ȼ����������������ʱ
	{  Postfixexp+=a.top(); a.pop();  }
	a.push(temp);
	temp=str[i++];
     } 
   }//end while(temp!='\0')
   while(!a.empty())
    {  Postfixexp+=a.top();
	a.pop();
	}
   Postfixexp+='\0';
   //cout<<Postfixexp;
   post2tree(p,Postfixexp);

}


void count(Node *p,int &height,int n) {//�����ĸ߶�
	if(p->left==NULL&&p->right==NULL)
	{  if(n>height)
	   height=n;}
	 if(p->left!=NULL)
		count(p->left,height,n+1);
	 if(p->right!=NULL)
	    count(p->right,height,n+1);
}

void paint(Node *p)//��ӡ��
{
   int height=0;
   int h=0;
   int i;
  using std::queue;
  queue<Node*> aQueue;
  count(p,height,1);
Node *pointer=p;
 Node *lastpointer;
 if(pointer)
	{ pointer->s=1;
      pointer->t=1;
 aQueue.push(pointer);  }
  while(!aQueue.empty())
 {  lastpointer=pointer;
	 pointer=aQueue.front();
 aQueue.pop();
 if(pointer->s>h)
 {cout<<endl;
  h=pointer->s;}
 if(pointer->t==1)
 {for(i=0;i<pow(2,height-pointer->s)-1;i++)
 cout<<" ";}
 else if(lastpointer->s!=pointer->s){
for(i=0;i<(pointer->t-1)*(pow(2,height-pointer->s+1)-1)+(pointer->t-1)-1+pow(2,height-pointer->s);i++)
	 cout<<" ";  }
 else 
{ for(i=0;i<(pointer->t-lastpointer->t)*(pow(2,height-pointer->s+1)-1)+(pointer->t-lastpointer->t)-1;i++)
 cout<<" ";  }
cout<<pointer->oper;
 if(pointer->left!=NULL){
	 pointer->left->s=pointer->s+1;
	 pointer->left->t=pointer->t*2-1;
	 aQueue.push(pointer->left);}
	 if(pointer->right!=NULL){
	 pointer->right->s=pointer->s+1;
	 pointer->right->t=pointer->t*2;
     aQueue.push(pointer->right);
     }  }  }


int main()
{ 
	string expression;
    Node *tree;
	
	cout<<"ǰ׺���ʽ-1 ��׺���ʽ0 ��׺���ʽ1"<<endl;
	int flag;
	cin>>flag;
    cout<<"��������ʽ:"<<endl;
    cin>>expression;
   
	if(flag==-1)//��ô��ǰ׺���ʽ
   pre2tree(tree,expression);  
   else if(flag==1)//��ô�Ǻ�׺���ʽ
   post2tree(tree,expression);
   else //������׺���ʽ
	 in2tree(tree,expression);  

   paint(tree);
   cout<<endl;

   
   cout<<"ǰ׺���ʽΪ:";
   preOrder(tree);
   cout<<endl; 
   cout<<"��׺���ʽΪ:";
   inOrder(tree);
   cout<<endl; 
   cout<<"��׺���ʽΪ:";
   postOrder(tree);
   cout<<endl;
   freeTree(tree);
   cout<<endl;
   
return 0; 
 }

