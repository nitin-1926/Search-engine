#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/stat.h>


struct page
{
    char page_url[200];
    int page_count;
    struct page * page_next;
    struct page * page_prev;
};

struct word
{
    char word_name[50];
    struct page * head_page;
    struct page * tail_page;
    struct word * word_next;
    struct word * word_prev;
    int word_key;
    int word_count;
};

struct Hash
{
    struct word * first;
    struct word * last;
};

struct Hash hash[30];

struct word *head=NULL,*last=NULL;

void initialise()
{
    int i;
    for(i=0;i<30;i++)
    {
        hash[i].first=NULL;
        hash[i].last=NULL;
    }
}

struct page *create_a_page_node(char url[])
{
    struct page *pg = (struct page*)calloc(1,sizeof(struct page));
    strcpy(pg->page_url,url);
    pg->page_count = 1;
    pg->page_next = NULL;
    return pg;
}

void first_node(struct word *temp,int key,char url[])
{
    struct page *pg=NULL;
    hash[key].first = temp;
    hash[key].last = temp;
    pg=create_a_page_node(url);
    pg->page_prev = NULL;
    temp->head_page = pg;
    temp->tail_page = pg;
    temp->word_next = NULL;
    temp->word_count = 1;
    last=temp;
}

void put_in_file()
{
    struct word *temp=head;
    struct page *tmp=NULL;
    FILE *file=fopen("/home/nitin/Desktop/Engine/indexerfile.txt","w");
    while(temp)
    {
        fprintf(file,"%s %d\n",temp->word_name,temp->word_count);
        tmp=temp->head_page;
        while(tmp)
        {
            fprintf(file,"%s %d\n",tmp->page_url,tmp->page_count);
            tmp=tmp->page_next;
        }
        fprintf(file,"\n");
        temp=temp->word_next;
    }
}

void put_in_list(char w[],char url[])
{
    struct word *temp=(struct word*)calloc(1,sizeof(struct word));
    struct page *pg=NULL;
    strcpy(temp->word_name,w);
    int key=strlen(w);
    temp->word_key=key;
    if(head==NULL)
    {
        head = temp;
        first_node(temp,key,url);
        temp->word_prev = NULL;
    }
    else
    {
        if(hash[key].first==NULL)
        {
            last->word_next = temp;
            temp->word_prev = last;
            first_node(temp,key,url);
        }
        else
        {
            if(strcmp(hash[key].first->word_name,temp->word_name)==0)
            {
                hash[key].first->word_count+=1;
                if(strcmp(hash[key].first->tail_page->page_url,url)==0)
                    hash[key].first->tail_page->page_count+=1;
                else
                {
                    pg = create_a_page_node(url);
                    pg->page_prev = hash[key].first->tail_page;
                    hash[key].first->tail_page->page_next = pg;
                    hash[key].first->tail_page = pg;
                }

                free(temp);
                return;
            }
            if(strcmp(hash[key].last->word_name,temp->word_name)==0)
            {
                hash[key].last->word_count+=1;
                if(strcmp(hash[key].last->tail_page->page_url,url)==0)
                    hash[key].last->tail_page->page_count+=1;
                else
                {
                    pg=create_a_page_node(url);
                    pg->page_prev = hash[key].last->tail_page;
                    hash[key].last->tail_page->page_next = pg;
                    hash[key].last->tail_page = pg;
                }
                free(temp);
                return;
            }
            struct word *trav = hash[key].first;
            while(trav&&trav->word_key==key)
            {
                if(strcmp(trav->word_name,temp->word_name)==0)
                {
                    trav->word_count+=1;
                    if(strcmp(trav->tail_page->page_url,url)==0)
                        trav->tail_page->page_count+=1;
                    else
                    {
                        pg=create_a_page_node(url);
                        pg->page_prev = hash[key].last->tail_page;
                        trav->tail_page->page_next = pg;
                        trav->tail_page = pg;
                    }
                    free(temp);
                    return;
                }
                trav=trav->word_next;
            }
            if(trav==NULL)
            {
                last=temp;
                temp->word_next = NULL;
                hash[key].last->word_next = temp;
                temp->word_prev = hash[key].last;
            }
            else
            {
                temp->word_next = trav;
                temp->word_prev = trav->word_prev;
                trav->word_prev = temp;
                hash[key].last->word_next = temp;
            }
            hash[key].last=temp;
            temp->word_count = 1;
            temp->head_page = NULL;
            temp->tail_page = NULL;
            pg=create_a_page_node(url);
            pg->page_prev = NULL;
            temp->head_page = pg;
            temp->tail_page = pg;
        }
    }
}

void print_list()
{
    struct word *temp=head;
    struct page *tmp=NULL;
    while(temp)
    {
        printf("%s %d \n",temp->word_name,temp->word_count);
        tmp=temp->head_page;
        while(tmp)
        {
            printf("%s %d \n",tmp->page_url,tmp->page_count);
            tmp=tmp->page_next;
        }
        printf("\n-----------\n");
        temp=temp->word_next;
    }
}

char* copy_content(FILE *file,int file_size)
{
    char *html_buffer=(char*)calloc(1,file_size);
    int i=0;
    char ch;
    while((ch=fgetc(file))!=EOF)
    {
        html_buffer[i++]=ch;
    }
    html_buffer[i]='\0';
    return html_buffer;
}

void rem_spa(char s[])
{
	int i=0,j=0,f=0;
  char ch;
	while(s[i]!='\0')
	{
    ch=s[i];
		if(ch==' '||ch==':'||ch=='.'||ch==')'||ch=='!')
		{
			s[i]='\0';
		}
		i++;
	}
}

void extract_words(char *start,char *end,char url[])
{
    char word[100]={0};
    int k=0;
    if(start==end)
    {
      printf("\n1\n");
    }
    for(;start!=end;start++)
    {
        if(*start==' '||*start==','||*start=='-'||*start=='.'||*start==':'||*start==';'||*start=='#'||*start=='&')
        {
            if(start+1==end)
            {
                word[k++]=*start;
            }
            word[k]='\0';
            rem_spa(word);
            if(k>1&&((word[0]>='A'&&word[0]<='Z')||(word[0]>='a'&&word[0]<='z')))
            put_in_list(word,url);
            k=0;
            word[0]='\0';
        }
        else
        {
            word[k++]=*start;
        }
    }
}

void read_file(int file_size,char *html)
{
    char title[]="title";
    int i=0,f=1;
    char url[200]={0};
    while(html[i]!='\n')
    {
        url[i]=html[i];
        i++;
    }
    url[i]='\0';
    i++;
    for(;i<file_size;i++)
    {
        if(html[i]=='<')
        {
            if(html[i+1]=='t'&&f)
            {
                char subbuff[6]={0};
                memcpy( subbuff, &html[i+1], 5 );
                subbuff[5] = '\0';
                if(strcmp(subbuff,title)==0)
                {
                    char *start=NULL,*end=NULL;
                    start = &html[i];
                    start = strpbrk(start,">");
                    start++;
                    end = strpbrk(start,"<");
                    extract_words(start,end,url);
                    f=0;
                    continue;
               //     i=i+end-start+2;
                }
            }
            if(html[i+1]=='h'&&html[i+2]>='1'&&html[i+2]<='6')
            {
                char *start=NULL,*end=NULL;
                start = &html[i];
                start = strpbrk(start,">");
                start++;
                /*
                while(*start=='<')
                {
                    start = strpbrk(start,">");
                    start++;
                }
                */
                end = strpbrk(start,"<");
                extract_words(start,end,url);
            //    i=i+end-start+2;
            }
        }
    }
}

int main()
{
    initialise();
    int c=1;
    while(1)
    {
        char file_name[10]={0},path_name[100]={0},*html=NULL;
        sprintf(file_name,"%d",c);
        strcat(file_name,".txt");
        strcat(path_name,"/home/nitin/Desktop/Engine/");
        strcat(path_name,file_name);
        FILE *file = fopen(path_name,"r");
        if(file)
        {
            struct stat st;
            stat(path_name,&st);
            int file_size=st.st_size;
						html=copy_content(file,file_size);
            read_file(file_size,html);
            //free(html);
						html=NULL;
        }
        else
        {
            printf("\n---end---\n");
            break;
        }
        break;
        c++;
    }
    print_list();
    put_in_file();
}
