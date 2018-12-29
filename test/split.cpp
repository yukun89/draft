#include<string>
#include<vector>
#include<cstdio>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
using namespace std;

void* prase_string(void* thread){
        string* s = (string*)thread;
        std::vector<std::string> fields;
cout<<hex<<(long)s->c_str()<<endl;
        boost::split(fields, *s, boost::is_any_of("_"), boost::token_compress_on);
cout<<hex<<(long)s->c_str()<<endl;
	string test;
cout<<hex<<(long)test.c_str()<<endl;
        for (int i = 0; i < fields.size(); ++i) {
                std::cout<< fields[i] <<std::endl;
        }
}

int main(){
        pthread_t pid;
	char *a="1234";
        string str = "test_tes_te_t";
        string str2 = "test_tes_te_t";
	printf("a:%x",a);
cout<<hex<<(long)str.c_str()<<endl;
cout<<hex<<(long)str2.c_str()<<endl;
        for(int i = 0; i < 2; i++){
                pthread_create(&pid, NULL, prase_string, (void*)&str);

        }
	while(true);
        return 0;

}
