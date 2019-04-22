#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#define SEED_URL "http://www.chitkara.edu.in";
struct Link
{
  int Link_key;
  int Link_flag;
  char *Link_url;
//      struct Link *node_prev;
  struct Link *Link_next;
  int Link_depth;
};
struct Hash
{
  struct Link* first;
  struct Link* last;
  int count;
};
struct Hash hash[50];
struct Link *head=NULL,*last=NULL;
void initialise()
{
  int i;
  for(i=0;i<50;i++)
  {
    hash[i].first=NULL;
    hash[i].last=NULL;
    hash[i].count=0;
  }
}
int generate_key(char *url)
{
  int i,l=strlen(url),key=0;
  //return strlen(url)%50;
  for(i=0;i<l;i++)
  {
    key+=(int)(url[i]);
  }
  return key%50;
}
void print_list(struct Link *head)
{
  struct Link *temp=head;
  while(temp!=NULL)
  {
    printf("key = %d Link = %s depth = %d flag= %d\n",temp->Link_key,temp->Link_url,temp->Link_depth,temp->Link_flag);
    temp=temp->Link_next;
  }
}
/*void save_links_in_file(struct Link* head)
{
  FILE *ptr=fopen("/home/nitin/Desktop/Engine/temp.txt","w");
  struct Link *temp=head;
  while(temp!=NULL)
  {
    fprintf(ptr,"%s ",temp->Link_url);
    fprintf(ptr,"%d ",temp->Link_key);
    fprintf(ptr,"%d ",temp->Link_depth);
    fprintf(ptr,"%d\n",temp->Link_flag);
    temp=temp->Link_next;
  }
}
void retrieve_links_in_list()
{
  initialise();
  head=NULL;
  FILE *ptr=fopen("/home/nitin/Desktop/Engine/temp.txt","r");
  char ch;
  char c[150]={0};
  char url[125]={0};
  char *urlss=NULL;
  int i=0,j=0,k=0;
  struct Link *trav;
  while((ch=fgetc(ptr))!=EOF)
  {
    if(ch=='\n')
    {
      c[i]='\0';
      i=0;
      struct Link *temp=(struct Link*)calloc(1,sizeof(struct Link));
      j=0;
      k=0;
      while(c[k]!=' ')
      {
        url[j]=c[k];
        j++;
        k++;
      }
      url[j]='\0';
      urlss=(char*)calloc(1,100);
      strcpy(urlss,url);
//       printf("\n%s\n",url);
      temp->Link_key=generate_key(url);         // put key
      int key=temp->Link_key;
      temp->Link_url=urlss;
  //   strcpy(temp->Link_url,url);                       // put url
      k++;
      j=0;
      while(c[k]!=' ')
      {
        k++;
      }
      k++;
      while(c[k]!=' ')
      {
        url[j]=c[k];
        j++;
        k++;
      }
      url[j]='\0';
      temp->Link_depth=atoi(url);                // put depth
      j=0;
      k++;
      while(c[k]!='\0')
      {
        url[j]=c[k];
        j++;
        k++;
      }
      url[j]='\0';
      temp->Link_flag=atoi(url);                   // put flag
      if(head==NULL)
      {
        temp->Link_next=NULL;
        head=temp;                      //   temp->Link_flag=1;
        last=temp;
        hash[key].first=temp;
        hash[key].last=temp;
        hash[key].count=1;
        continue;
      }
      else
      {
        if(hash[key].first==NULL)
        {
          last->Link_next=temp;
          temp->Link_next=NULL;
          last=temp;
          hash[key].first=temp;
          hash[key].last=temp;
          hash[key].count=1;
        }
        else
        {
          trav=hash[key].first;
          if((strcmp(hash[key].first->Link_url,temp->Link_url)==0)||(strcmp(hash[key].last->Link_url,temp->Link_url)==0))
          {
            free(temp);
            free(urlss);
            continue;
          }
          int f=0;
          while(trav->Link_next!=NULL&&trav->Link_next->Link_key==key)
          {
            if(strcmp(trav->Link_url,temp->Link_url)==0)
            {
              free(temp);
              f=1;
              break;
            }
            trav=trav->Link_next;
          }
          if(f)
          continue;
          if(trav->Link_next==NULL)
          last=temp;
          temp->Link_next=trav->Link_next;
          trav->Link_next=temp;
          hash[key].last=temp;
          hash[key].count++;
        }
      }
      c[0]='\0';
    }
    else
    {
      c[i++]=ch;
    }
  }
  print_list(head);
}*/
void put_links_in_list(char **result,int l,int depth)
{
  int i;
  struct Link *temp,*trav;
  for(i=0;i<l;i++)
  {
    temp=(struct Link*)calloc(1,sizeof(struct Link));
    temp->Link_key=generate_key(result[i]);
    int key=temp->Link_key;
    temp->Link_url=result[i];
    temp->Link_depth=depth+1;
    if(head==NULL)
    {
      temp->Link_next=NULL;
      temp->Link_flag=1;
      temp->Link_depth=0;
      head=temp;                      //   temp->Link_flag=1;
      last=temp;
      hash[key].first=temp;
      hash[key].last=temp;
      hash[key].count=1;
      continue;
    }
    else
    {
      if(hash[key].first==NULL)
      {
         last->Link_next=temp;
         temp->Link_next=NULL;
         temp->Link_flag=0;
         last=temp;
         hash[key].first=temp;
         hash[key].last=temp;
         hash[key].count=1;
      }
      else
      {
        trav=hash[key].first;
        if((strcmp(hash[key].first->Link_url,temp->Link_url)==0)||(strcmp(hash[key].last->Link_url,temp->Link_url)==0))
        {
          free(temp);
          continue;
        }
        int f=0;
        while(trav->Link_next!=NULL&&trav->Link_next->Link_key==key)
        {
          if(strcmp(trav->Link_url,temp->Link_url)==0)
          {
            free(temp);
            f=1;
            break;
          }
          trav=trav->Link_next;
        }
        if(f)
        continue;
        if(trav->Link_next==NULL)
        last=temp;
        temp->Link_flag=0;
        temp->Link_next=trav->Link_next;
        trav->Link_next=temp;
        hash[key].last=temp;
        hash[key].count++;
      }
    }
  }
//  save_links_in_file(head);
}
char* get_next_url(int depth)
{
  struct Link *temp=head;
  while(temp)
  {
    if(temp->Link_flag==0&&temp->Link_depth==depth)
    {
      temp->Link_flag=1;
      return temp->Link_url;
    }
    temp=temp->Link_next;
  }
  return NULL;
}
int seedcheck(char ch[])
{
  char *check=(char*)calloc(1000,1);
  strcat(check,"wget --spider ");
  strcat(check,ch);
  strcat(check," >/dev/null 2>&1");
  if(!system(check))
  return 1;
  else
  return 0;
}
void depth(int d)
{
//  int d=atoi(ch);
/*
  int flag=0;
  for(int i=0;ch[i]!='\0';i++)
    {
      if(ch[i]>='0'&&ch[i]<='9')
      flag=0;
      else
      {
        flag=1;
        break;
      }
    }
  if(flag==0)
  {
    */
    if(d>=1&&d<=5)
    printf("depth is correct\n");
    else
    printf("depth is not correct\n");
/*  }
  else
  printf("incorrect numeric value\n");
  */
}
void testDir(char *dir)
{
  struct stat statbuf;
  if ( stat(dir, &statbuf) == -1 )
  {
    fprintf(stderr, "-----------------\n");
    fprintf(stderr, "Invalid directory\n");
    fprintf(stderr, "-----------------\n");
    exit(1);
  }

  //Both check if there's a directory and if it's writable
  if ( !S_ISDIR(statbuf.st_mode) )
  {
    fprintf(stderr, "-----------------------------------------------------\n");
    fprintf(stderr, "Invalid directory entry. Your input isn't a directory\n");
    fprintf(stderr, "-----------------------------------------------------\n");
    exit(1);
  }

  if ( (statbuf.st_mode & S_IWUSR) != S_IWUSR )
  {
    fprintf(stderr, "------------------------------------------\n");
    fprintf(stderr, "Invalid directory entry. It isn't writable\n");
    fprintf(stderr, "------------------------------------------\n");
    exit(1);
  }
}
void getpage(char *url,char ch[])
{
  char urlbuffer[300]="wget -O ";
  strcat(urlbuffer,"/home/nitin/Desktop/Engine/");
  strcat(urlbuffer,"temp.txt ");
  strcat(urlbuffer,url);
  system(urlbuffer);
  printf("**************PAGE GOT****************\n");
}
void chngDir(char *dir)
{
  static int index=1;
  char fName[100]={0},ch;
  char temp[100]={0};
  sprintf(fName,"%d",index);     //onverts integer to string
  strcat(fName,".txt");
  strcat(temp,dir);
  strcat(temp,fName);
  FILE *old = fopen("/home/nitin/Desktop/Engine/temp.txt","r");
  FILE *new = fopen(temp, "w");
  ch = getc(old);
  while(ch != EOF)
  {
    putc(ch,new);
    ch = getc(old);
  }
  index++;
  printf("New File Created in Target Directory\n");
  //fclose(old);
  fclose(new);
}
// FILE: html.c

// HTML parser utility implementation
// see html.h for detail usage

/*

*removeWhiteSpace*
------------------

Description: Removes the white space characters from the input
string buffer that contains the html content. This function
basically scans through the entire html buffer content character
by character, and abandons any white space character it encounters.
The ASCII code of the characters are used to determine whether
a character is a white space or not; Characters with ASCII code
values below 32 are considered white space characters, and are
thus removed.

Input: string_buffer

** Pseudo Code **

(1) Create a target buffer one character than the input buffer, and clear it
(2) FOR (Every character in the input buffer) DO
      IF (the current character is not a while space character) THEN
        Append it to the end of the target buffer
      END
    DONE
(3) Overwrite the input buffer with the target buffer
(4) Release targer buffer

*****

*/
void removeWhiteSpace(char* html)
{
  int i;
  char *buffer = malloc(strlen(html)+1), *p=malloc (sizeof(char)+1);
  memset(buffer,0,strlen(html)+1);
  for (i=0;html[i];i++)
  {
    if(html[i]>32)
    {
      sprintf(p,"%c",html[i]);
      strcat(buffer,p);
    }
  }
  strcpy(html,buffer);
  free(buffer); free(p);
}

/*

*GetNextURL*
------------

Description: Given a HTML string buffer, the URL of the HTML,
and a position index, find the closest URL after the position
and copy the URL into the result buffer, which is also an input
argument. This function is the main component of the HTML parser.
This function is designed such that it is meant to be repeatedly
called toextract URLs from the HTML one at a time, starting from the
beginning of the HTML and terminating when the end of the HTML
is reached. The return value of this function is meant for the
repeated calls of this function; the real return value is the
third input argument, which is the result buffer, in which a
new URL will be written if one is found. This function can
handle normal absolute and relative URLs generally  found in
the <a href=""> tags; however, more extreme cases, like this
<a href="../../../a.txt">, are not currently being extracted.

Input: html_buffer, urlofthispage, result_buffer, current_position

Return: Position of the URL found

** Pseudo Code **

(1) IF (first call) THEN
      Remove white space characters from the page
    END
(2) Find the <a> or <A> html tags by scanning through the html text
(3) Keep going until we may have found a URL
(4) IF (It actually is NOT a URL, which has multiple possibilities) THEN
      Recursively call self from the next position
    END
(5) IF (It is an absolute URL) THEN
      Set result buffer to contain this URL
      Return the current position
    ELSE (It is an relative URL) THEN
      Produce the result URL by combining the relative URL with the urlofthispage
      Set result buffer to contain this URL
      Return the current position
    END
(7) Return -1 to signal completion

*****

*/

int GetNextURL(char* html, char* urlofthispage, char* result, int pos)
{
  char c;
  int len, i, j;
  char* p1;  //!< pointer pointed to the start of a new-founded URL.
  char* p2;  //!< pointer pointed to the end of a new-founded URL.

  // NEW
  // Clean up \n chars
  if(pos == 0) {
    removeWhiteSpace(html);
  }
  // /NEW

  // Find the <a> <A> HTML tag.
  while (0 != (c = html[pos]))
  {
    if ((c=='<') &&
        ((html[pos+1] == 'a') || (html[pos+1] == 'A'))) {
      break;
    }
    pos++;
  }
  //! Find the URL it the HTML tag. They usually look like <a href="www.abc.com">
  //! We try to find the quote mark in order to find the URL inside the quote mark.
  if (c)
  {
    // check for equals first... some HTML tags don't have quotes...or use single quotes instead
    p1 = strchr(&(html[pos+1]), '=');

    if ((!p1) || (*(p1-1) == 'e') || ((p1 - html - pos) > 10))
    {
      // keep going...
      return GetNextURL(html,urlofthispage,result,pos+1);
    }
    if (*(p1+1) == '\"' || *(p1+1) == '\'')
      p1++;

    p1++;

    p2 = strpbrk(p1, "\'\">");
    if (!p2)
    {
      // keep going...
      return GetNextURL(html,urlofthispage,result,pos+1);
    }
    if (*p1 == '#')
    { // Why bother returning anything here....recursively keep going...

      return GetNextURL(html,urlofthispage,result,pos+1);
    }
    if (!strncmp(p1, "mailto:",7))
      return GetNextURL(html, urlofthispage, result, pos+1);
    if (!strncmp(p1, "http", 4) || !strncmp(p1, "HTTP", 4))
    {
      //! Nice! The URL we found is in absolute path.
      strncpy(result, p1, (p2-p1));
      return  (int)(p2 - html + 1);
    } else {
      //! We find a URL. HTML is a terrible standard. So there are many ways to present a URL.
      if (p1[0] == '.') {
        //! Some URLs are like <a href="../../../a.txt"> I cannot handle this.
    // again...probably good to recursively keep going..
    // NEW

        return GetNextURL(html,urlofthispage,result,pos+1);
    // /NEW
      }
      if (p1[0] == '/') {
        //! this means the URL is the absolute path
        for (i = 7; i < strlen(urlofthispage); i++)
          if (urlofthispage[i] == '/')
            break;
        strcpy(result, urlofthispage);
        result[i] = 0;
        strncat(result, p1, (p2 - p1));
        return (int)(p2 - html + 1);
      } else {
        //! the URL is a absolute path.
        len = strlen(urlofthispage);
        for (i = (len - 1); i >= 0; i--)
          if (urlofthispage[i] == '/')
            break;
        for (j = (len - 1); j >= 0; j--)
          if (urlofthispage[j] == '.')
              break;
        if (i == (len -1)) {
          //! urlofthis page is like http://www.abc.com/
            strcpy(result, urlofthispage);
            result[i + 1] = 0;
            strncat(result, p1, p2 - p1);
            return (int)(p2 - html + 1);
        }
        if ((i <= 6)||(i > j)) {
          //! urlofthis page is like http://www.abc.com/~xyz
          //! or http://www.abc.com
          strcpy(result, urlofthispage);
          result[len] = '/';
          strncat(result, p1, p2 - p1);
          return (int)(p2 - html + 1);
        }
        strcpy(result, urlofthispage);
        result[i + 1] = 0;
        strncat(result, p1, p2 - p1);
        return (int)(p2 - html + 1);
      }
    }
  }
  return -1;
}

/*

*NormalizeWord*
---------------

Description: Make sure all the Roman letters in the URL are
of lower cases, for ease of carrying out string comparison in
the future when trying to decide if two URL are the same or not.
Basically a linear scan, starting from the beginning of the URL,
is performed. Whenever a capital letter character is encountered
(by checking its ASCII code value), it is replaced by the
corresponding lower case letter.

Input: input_url

** Pseudo Code **

(1) FOR (every character in the input string) DO
      IF (this character is a capital letter) DO
        Change this letter to lower case
      END
    DONE

*****

*/

void NormalizeWord(char* word)
{
  int i = 0;
  while (word[i]) {
      // NEW
    if (word[i] < 91 && word[i] > 64) // Bounded below so this funct. can run on all urls
      // /NEW
      word[i] += 32;
    i++;
  }
}

/*

*NormalizeURL*
--------------

Description: Normalize the input URL string and return its validity.
The normalization contains two major components: first, if the
URL ends with a trailing slash '/' character, this trailing slash
will be removed from the URL; and second, if the URL points to
a file (with an extension), then only certain file extensions are
accepted; currently, acceptable normal file extensions start with
.htm, .HTM, .php, or .jsp. A URL is valid if it is long enough and,
if pointing to a file, points to a file of acceptable format;
otherwise the URL is considered invalid and therefore will not
be added to the url_list for future processing.

Input: input_url

Output: validity of the input URL: 0 - invalid
                                   1 - valid

** Pseudo Code **

(1) Return error signal if input url is too short.
(2) IF (input url ends with '/') THEN
      Remove the '/'
    END
(3) Find the positions of the last occurrences of '/' and '.'
(4) IF (the '/' and '.' are positioned s.t. they indicate the url points to a file) THEN
      IF (the file extension starts with .htm or .HTM or .php or .jsp) THEN
        Do nothing...
      ELSE
        Return bad url signal
      END
    END
(5) Return good url signal

*****

*/

int NormalizeURL(char* URL)
{
  int len = strlen(URL);
  if (len <= 1 )
    return 0;
  //! Normalize all URLs.
  if (URL[len - 1] == '/')
  {
    URL[len - 1] = 0;
    len--;
  }
  int i, j;
  len = strlen(URL);
  //home/pardeep/nitin/
  //! Safe check.
  if (len < 2)
    return 0;
  //! Locate the URL's suffix.
  for (i = len - 1; i >= 0; i--)
    if (URL[i] =='.')
      break;
  for (j = len - 1; j >= 0; j--)
    if (URL[j] =='/')
      break;
  //! We ignore other file types.
  //! So if a URL link is to a file that are not in the file type of the following
  //! one of four, then we will discard this URL, and it will not be in the URL list.
  if ((j >= 7) && (i > j) && ((i + 2) < len))
  {
    if ((!strncmp((URL + i), ".htm", 4))
        ||(!strncmp((URL + i), ".HTM", 4))
        ||(!strncmp((URL + i), ".php", 4))
        ||(!strncmp((URL + i), ".jsp", 4))
        )
    {
      len = len; // do nothing.
    }
    else
    {
      return 0; // bad type
    }
  }
  return 1;
}

char* convertDataInStr()
{
  //printf("In function convert\n");
  struct stat st; //variable which will count length of file.
  stat("/home/nitin/Desktop/Engine/temp.txt",&st); // temp.txt is the file where wget fetch the html
  int file_size=st.st_size;
  //printf("In function convert after file size\n");
  char *temp_str = (char*) malloc(sizeof(char)*file_size+1);
  int i=0;
  char ch;
  FILE *old = fopen("/home/nitin/Desktop/Engine/temp.txt","r");
  //printf("In function convert after opening\n");
  ch = getc(old);
  while(ch != EOF)
  {
    temp_str[i]=ch;
    ch = getc(old);
    i++;
  }
  //printf("In function convert after while loop\n");
  temp_str[i]='\0';
  //fclose(old);
  //printf("In function convert after closing\n");

  return temp_str;
}
void run(char *url, int depthh, char *dir)
{
//  int depthh=atoi(ch);
  int check;
  char seed_url[100];
  strcpy(seed_url,url);
  check=seedcheck(seed_url);
  if(check)
  {
    printf("Url Is Correct\n");
    depth(depthh);
    testDir(dir);
    getpage(seed_url,dir);
    chngDir(dir);
    char *fcontent = convertDataInStr();
    printf("\nafter convertDataInStr\n");
    int pos=0;
  //  char **links = (char**) malloc(sizeof(char)*100);
    char *links[100];
    for(int i = 0;i<100&&pos<160908;i++)
    {
      links[i] = (char*) calloc(500,1);
      pos = GetNextURL(fcontent, url, links[i], pos);
    }
    char *links_final[100];
    for(int i=0;i<100;i++)
    {
      links_final[i] = (char*) malloc(sizeof(char)*500);
    }
    int k=0;
    int flag=0;
    strcpy(links_final[0],links[0]);
    k++;
    for(int i=0;i<100;i++)
    {
      for(int j=0;j<k;j++)
      {
        if(strcmp(links_final[j],links[i]))
        {
          flag=0;
        }
        else
        {
          flag=1;
          break;
        }
      }
      if(flag==0)
      {
        strcpy(links_final[k++],links[i]);
      }
    }
    //for(int i=0;i<k;i++)
    //{
      //printf("%s\n",links_final[i]);
    //}
    put_links_in_list(links_final,k,depthh);
  }
  else
  printf("404 NOT FOUND\n");
}
int main(int argc,char *argv[])
{
    run(argv[1],atoi(argv[2]),argv[3]);
    printf("\nIN main back\n");
    int depth=1;
    char *url=NULL;
    while(depth<=5)
    {
      printf("\nin outer looop\n");
      while((url=get_next_url(depth))!=NULL)
      {
        printf("\nin inner looop\n");
        run(url,depth,argv[3]);
      }
      depth++;
    }
}
