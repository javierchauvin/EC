#include "Intro.hpp"

template <int number>
UserIntro<number>::UserIntro(){
}
template <int number>
UserIntro<number>::~UserIntro(){
    user.CleanUp();
}
template <int number>
void UserIntro<number>::Set(const char from[]){
    user.Set(from);
}
template <int number>
void UserIntro<number>::Run(){
    int terminate = 1;
    
    //FsOpenWindow(16,16,800,600,1);
    TextInput t;
    
    while(terminate == 1){
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        TextString output;
        char num[5];
        sprintf(num, "%d", number);
        output.Set("Please enter user");
        output.Add(num);
        output.Add(" name: ");
        
        t.SetCaption(output.GetPointer());
        t.SetDefaultText("");
        terminate = t.IntroInput(); // input test: if FSKEY_END, terminate becomes 0
        if(0!=terminate){
            // printf("%s\n", t.GetString());
            user.Set(t.GetString());
            terminate = 0;
        }
        FsSwapBuffers();
        FsSleep(0);
    }
}
template<int number>
TextString UserIntro<number>::GetUser(){
    return user;
}

// ======================
// main function for Intro

void Intro(TextString * UserName1, TextString * UserName2){
    //FsOpenWindow(16,16,800,600,1);
    UserIntro1 user1;
    UserIntro2 user2;
    user1.Run();
    user2.Run();
    
    UserName1->Set(user1.GetUser().GetPointer());
    UserName2->Set(user2.GetUser().GetPointer());
}
