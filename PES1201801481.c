#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"

         
char* intal_add(const char* intal1,const  char* intal2)
{
    int lenintal1=strlen(intal1);  
    int lenintal2=strlen(intal2);
    int lenintal3;
    if(lenintal1>lenintal2)
    {
        lenintal3 = lenintal1+2;
    }      
    else
    {
        lenintal3 = lenintal2+2;
    }

    if(intal_compare(intal1,"0")==0)
    {
        char* result = (char*)malloc(sizeof(char)*strlen(intal2));
        strcpy(result,intal2);
        return result;
    }
    if(intal_compare(intal2,"0")==0)
    {
        char* result = (char*)malloc(sizeof(char)*strlen(intal1));
        strcpy(result,intal1);
        return result;
    }
    
    char* result=(char*)malloc(lenintal3*sizeof(char));
    result[lenintal3-1]='\0';

    int sum=0;
    int carry=0;
    int i = 0;
    for(;lenintal1-i-1 >=0 && lenintal2-i-1>=0;)
    {
        sum=(intal1[lenintal1-i-1]-'0') + (intal2[lenintal2-i-1]-'0') + carry;
        result[lenintal3-i-2]=(char)sum%10+'0';
        carry=sum/10;
        i++;
    }

    while(i<lenintal1 && lenintal1-i-1>=0)
    {
        sum=(intal1[lenintal1-i-1]-'0') + carry;
        result[lenintal3-i-2]=(char)sum%10+'0';
        carry=sum/10;
        i++;
    }

    while(i<lenintal2 && lenintal2-i-1>=0)
    {
        sum=(intal2[lenintal2-i-1]-'0') + carry;
        result[lenintal3-i-2]=(char)sum%10+'0';
        carry=sum/10;
        i++;
    }

    if(carry>0)
        result[0]=(char)carry+'0';
    else
    {
        int i=0;
        while(i<lenintal3-1)
        {
            result[i]=result[i+1];
            i++;
        }
        result[lenintal3-1]='\0';
    }
    return result;
}

int intal_compare(const char* intal1, const char* intal2)
{
    int lenintal1 = strlen(intal1);
    int lenintal2 = strlen(intal2);
    if (lenintal1>lenintal2)
        return 1;
    else if (lenintal2>lenintal1)
        return -1;
    else if (lenintal1==lenintal2)
    {
        for(int i=0; i!=lenintal2 ;)
        {
            if (intal1[i] == intal2[i])
                i++;
            else if (intal1[i] > intal2[i])
                return 1;
            else if (intal2[i] > intal1[i])
                return -1;
        }
    }
    return 0;
}

static void ulta(char *str)
{
    int length = strlen(str);
    for (int i = 0; i < length / 2; i++)
    {
        char b = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = b;
    }
}

char *intal_diff(const char *intal1, const char *intal2)
{
    char* str1 = malloc(sizeof(char) * (strlen(intal1) + 1));
    strcpy(str1,intal1);
    char* str2 = malloc(sizeof(char) * (strlen(intal2) + 1));
    strcpy(str2,intal2);
    int compare = intal_compare(str2, str1);
    if (compare == 0)
    {
        char *result = malloc(sizeof(char) * 2);
        result[0] = 48;
        result[1] = '\0';
        return result;
    }
    if (compare == 1)
    {
        char *temp = str1;
        str1 = str2;
        str2 = temp;
    }
    int a = strlen(str1);
    int b = strlen(str2);
    char *result;

    int n = a > b ? a : b;

    int minimum = (n == a) ? b : a;
    result = (char *)malloc(sizeof(char) * (n + 2));
    ulta(str1);
    ulta(str2);
    int c = 0;
    int m = 0;
    for (int i = 0; i < minimum; i++)
    {
        int s = (str1[i] - '0') - (str2[i] - '0') - c;
        if (s < 0)
        {
            s += 10;
            c = 1;
        }

        else
        {
            c = 0;
        }
        result[m++] = 48 + s;
    }

    for (int i = minimum; i < n; i++)
    {
        int s = (str1[i] - '0') - c;
        if (s < 0)
        {
            s += 10;
            c = 1;
        }
        else
        {
            c = 0;
        }
        result[m++] = 48 + s;
    }
    m--;
    while (result[m] == 48)
    {
        m--;
    }
    m++;
    result[m] = '\0';

    ulta(result);
    free(str1);
    free(str2);
    return result;
}

char* intal_multiply(const char* intal1,const  char* intal2)
{ 
    int lenintal1=strlen(intal1);
    int lenintal2=strlen(intal2);
    int lenintal3=lenintal1+lenintal2;

    if(intal_compare("0",intal1)==0 || intal_compare("0",intal2)==0)
    {
        char *result=(char*)malloc(2*sizeof(char));
        result[0]='0'; result[1]='\0';
        return result;
    }
    int *temp=(int*)malloc(lenintal3*sizeof(int));
    for(int i=0;i<lenintal3;i++)
        temp[i]=0;
    
    int i_len1=0;
    int i_len2=0;

    for(int i=lenintal1-1;i>=0;i--)
    {
        int x=intal1[i] - '0';
        int carry=0;
        i_len2=0;
        int j=lenintal2-1;
        while(j>=0)
        {
            int y=intal2[j] - '0';
            int sum=x*y + temp[i_len1 + i_len2] + carry;
            carry=sum/10;
            temp[i_len1 + i_len2]=sum%10;
            i_len2++;
            j--;
        }
        if(carry>0)
            temp[i_len1 + i_len2]+=carry;
        
        i_len1++;
    }
    int mul_i;
    mul_i = lenintal3 - 1;
    while(mul_i>=0 && temp[mul_i] == 0)
    {
        mul_i--;
    }
    
    char *result=(char*)malloc((mul_i+2)*sizeof(char));
    int mul_j = 0;
    while(mul_j<=mul_i)
    {
        result[mul_j]=temp[mul_i-mul_j]+'0';
        mul_j++;
    }
    result[mul_i+1]='\0';
    free(temp);
    return result;
}

char *intal_mod(const char *intal1, const char *intal2)
{
    int length1 = strlen(intal1);
    int length2 = strlen(intal2);
    if (intal_compare(intal1, intal2) == -1)
    {
        char *l = malloc(sizeof(char) * (length1 + 1));
        strcpy(l,intal1);
        return l;
    }
    int diff = length1 - length2;
    int r = 0;
    for (int i = 0; i < strlen(intal2); i++)
    {
        if (intal2[i] > intal1[i])
        {
            r = 1;
            break;
        }
        else if (intal1[i] > intal2[i])
        {
            r = 0;
            break;
        }
    }
    diff -= r;
    if (diff > 0)
    {
        char *e = malloc(sizeof(char) * (length2 + diff + 1));
        for (int i = 0; i < length2; i++)
        {
            e[i] = intal2[i];
        }
        int m = length2;
        for (int i = 0; i < diff; i++)
        {
            e[i + m] = 48;
        }
        e[diff + m] = '\0';
        e = intal_diff(intal1, e);
        return intal_mod(e, intal2);
    }
    return intal_mod(intal_diff(intal1, intal2), intal2);
}

char* intal_pow(const char* intal1, unsigned int n)
{
    if(intal_compare(intal1,"0") == 0){
        char* t_pow = (char*)malloc(sizeof(char)*2);
        t_pow[0] = '0';t_pow[1] = '\0';
        return t_pow;
    }
    char* num = (char*)malloc(sizeof(char)*strlen(intal1));
    strcpy(num,intal1);
    int y=n;
    char* temp_num;
    char* temp_result;
    char* result = (char*)malloc(sizeof(char)*2);
    result[0] = '1';result[1] = '\0';
    while(y>0){
        temp_num = num;
        if ((y%2) == 1){
            temp_result = result;
            result = intal_multiply(result,num);
            free(temp_result);
        }
        y = y/2;
        num = intal_multiply(num,num);
        free(temp_num);
    }
    free(num);
    return result;
}

char *intal_gcd(const char *intal1, const char *intal2)
{
    if (intal1[0] == 48 && intal2[0] == 48)
    {
        char *result = malloc(sizeof(char) * 2);
        result[1] = '\0';
        result[0] = 48;
        return result;
    }

    if (intal2[0] == 48)
    {
        char *result = malloc(sizeof(char) * (strlen(intal1) + 1));
        strcpy(result,intal1);
        return result;
    }
    else
    {
        return intal_gcd(intal2, intal_mod(intal1, intal2));
    }
}

char* intal_fibonacci(unsigned int n)
{
    char* a = (char*)malloc(sizeof(char)*2);
    a[0] = '0';a[1] = '\0';
    char* b = (char*)malloc(sizeof(char)*2);
    b[0] = '1';b[1] = '\0';
    if (n == 0)
    {
        free(b);
        return a;
    }
    if (n == 1){ 
        free(a);  
        return b;
    }
    char* temp_a;
    char* temp_res;
    int fib_i = 2;
    while(fib_i<=n)
    {
        temp_a = a;
        temp_res = intal_add(a,b);
        a = b;
        b = temp_res;
        free(temp_a);
        fib_i++;
    }
    free(a);
    return temp_res;
}

char* intal_factorial(unsigned int n)
{
    char* temp_factorial = (char*)malloc(sizeof(char)*2);
    char* factorial;
    strcpy(temp_factorial,"1\0");
    char* result = (char*)malloc(sizeof(char)*2);
    strcpy(result,"1\0");
    char* temp_result;
    int fact_i = 1;
    while(fact_i<=n)
    {
        temp_result = result;
        factorial = temp_factorial;
        result = intal_multiply(temp_factorial,result);
        free(temp_result);
        temp_factorial = intal_add(temp_factorial,"1");
        free(factorial);
        fact_i++;
    }
    free(temp_factorial);
    return result;
}

int intal_max(char **arr, int n)
{
    int max = 0;
    int compare;
    for(int i = 1;i<n;i++)
    {
        compare = intal_compare(arr[i],arr[max]);
        if (compare == 1)
            max = i;
    }
    return max;
}

int intal_min(char **arr, int n)
{
    int min = 0;
    int compare;
    for(int i = 1;i<n;i++)
    {
        compare = intal_compare(arr[min],arr[i]);
        if (compare == 1)
            min = i;
    }
    return min;
}

int intal_search(char **arr, int n, const char* key)
{
    int compare;
    int i=0;
    while(i<n)
    {
        compare = intal_compare(key,arr[i]);
        if (compare == 0)
            return i;
        i++;
    }
    return -1;
}

int intal_binsearch(char **arr, int n, const char* key)
{
    int low = 0;
    int high = n - 1;
    int compare;
    int mid;
    while(low<=high)
    {
        mid = (low + high)/2;
        compare = intal_compare(arr[mid],key);
        if (compare == 0)
            return mid;
        if (compare == 1)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

char* intal_bincoeff(unsigned int n, unsigned int k)
{
    int i,j;
    int kk=k;
    if(n-k<k)
    {
        kk=n-k;
    }
    char arr[kk+1][1001];
    for(i = 1; i < (kk+1); i++) 
    {
        strcpy(arr[i],"0");
    }
    strcpy(arr[0],"1");
    for(i=1;i<=n;i++)
    {
        for(j=((i<kk)?i:kk);j>0;j--)
        {
            char *result=intal_add(arr[j],arr[j-1]);
            strcpy(arr[j],result);
            free(result);
        }
    }
    char *result1=(char*)malloc(1001*sizeof(char));
    strcpy(result1,arr[kk]);
    return result1;
}  

static void intal_sort_heapify(char **arr,int n,int i)
{
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;
    if (left<n && intal_compare(arr[left],arr[largest]) == 1)
        largest = left;
    if(right<n && intal_compare(arr[right],arr[largest]) == 1)
        largest = right;
    if (largest != i)
    {
        char* temp = arr[largest];
        arr[largest] = arr[i];
        arr[i] = temp;
        intal_sort_heapify(arr,n,largest);
    }
}

void intal_sort(char **arr, int n)
{
    int i = (n/2 - 1);
    while(i>=0)
    {
        intal_sort_heapify(arr,n,i);
        i--;
    }
     
    int j=n-1;   
    while(j>0)
    {
        char* temp = arr[0];
        arr[0] = arr[j];
        arr[j] = temp;
        intal_sort_heapify(arr,j,0);
        j--;
    }
}

char* coin_row_problem(char **arr, int n)
{
    int compare;
    char *add;
    char *temp;
    char *cur,*prev,*next;
    prev = (char*)malloc(sizeof(char)*2);
    prev[0] = '0';prev[1] = '\0';
    cur = (char*)malloc(sizeof(char)*strlen(arr[0]));
    strcpy(cur,arr[0]);
    int coin_i=2;
    while(coin_i<=n)
    {
        temp = prev;
        add = intal_add(arr[coin_i - 1],prev);
        compare = intal_compare(add,cur);
        if(compare == 1)
            next = add;
        else
        {
            next = cur;
            free(add);
        }
        prev = cur;
        cur = next;
        coin_i++;
    }
    return cur;
}