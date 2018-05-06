#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<ctime>
#include<fstream>

#define OR ||
#define AND &&

using namespace std;
class PEND
{
    char unencryptedPassword[30];
    char encryptedPassword[70];
    int key;
    int raw;
    int passwordId;
public:
    PEND();
    void Encryption();
    void Decryption();
    void WFile();
    bool CheckID();

};

PEND::PEND()
{
    raw=0;
    srand(time(0));
    for(int i=0;i<=90;i++)
    {
        if(i%2==0)
        {
            encryptedPassword[i]=rand()%26+65;
            raw++;
            if(raw==2)
            {
                encryptedPassword[i]=rand()%26+97;
                raw=0;
            }
        }
        else
            encryptedPassword[i]=rand()%10+48;
    }
}


void PEND::Encryption()
{

    cout<<"\n\n PLEASE CHOOSE A SECRET ID FOR YOUR PASSWORD : ";
    cin >> passwordId;
    cout<<"\n\n ENTER YOUR PASSWORD FOR ENCRYPTION (BETWEEN 6-30 CHARACTERS) : ";
    cin >> unencryptedPassword;
    key=strlen(unencryptedPassword);
    while(key < 6 OR key > 31)
    {   cout << "\n\n SORRY!!!!PASSWORD MUST BE BETWEEN 6-30 CHARACTERS!!!!!\a\a\a\n\n";
        cout<<"\n\n ENTER YOUR PASSWORD AGAIN FOR ENCRYPTION (BETWEEN 6-30 CHARACTERS) : ";
        cin >> unencryptedPassword;
        key=strlen(unencryptedPassword);
    }

        for(int i=0;i<key;i++)
        {
            encryptedPassword[i*3]=unencryptedPassword[i]+(key/5);
        }

        encryptedPassword[key*3] = '\0';
        cout << "\n\n ENCRYPTED PASSWORD IS : " << encryptedPassword;
        cout<<"\n\n PLEASE DON'T GIVE YOUR SECRET ID TO ANYONE!!!!!!! \n\n";
        cout<<"\n\n YOU CAN ONLY ACCESS YOUR PASSWORD WITH THE SECRET KEY PROVIDED BY YOU .... \n\n";
        WFile();

}

void PEND::Decryption()
{
    cout << "\n\n ENTER THE ENCRYPTED PASSWORD : ";
    cin >> encryptedPassword;
    cout << "\n\n ENTER THE SECRET ID : ";
    cin >> passwordId;
    bool frv=CheckID();
    if(frv==0)
    {
      cout<<"\n\n SORRY!!! RECORD DOESN'T EXIST!!!!\a\a\a\n\n";
      cout<<"\n\n PLEASE CHECK YOUR SECRET ID OR ENCRYPTED PASSWORD ....\n\n ";
      cout<<"\n\n NOTE THAT THE PASSWORD IS CASE SENSITIVE......\n\n ";

    }
    else
    {
        key=strlen(encryptedPassword);
        raw=0;
        for(int i=0;i<key;i+=3)
        {
            unencryptedPassword[raw]=encryptedPassword[i];
            raw++;
        }
        unencryptedPassword[raw]='\0';
        key=strlen(unencryptedPassword);
        if(key>5)
        {
            for(int i=0;i<key;i++)
            {
                unencryptedPassword[i]-=(key/5);
            }
        }
        else
        {
            for(int i=0;i<key;i++)
                unencryptedPassword[i]-=key;
        }
        unencryptedPassword[key] = '\0';
        cout << "\n\n DECRYPTED PASSWORD IS : " << unencryptedPassword << endl << endl;
    }
}

void PEND::WFile()
{
    ofstream PFile("Password.txt", ios::app);
    PFile << passwordId << ' ' << encryptedPassword << endl;
    PFile.close();
}

bool PEND::CheckID()
{
    int Sid;
    string searchp;
    ifstream PFile("Password.txt");
    while(PFile >> Sid >> searchp)
    {
        if(Sid==passwordId AND searchp==encryptedPassword)
            return 1;
    }
    return 0;
}


int main()
{

       PEND a1;
       int choice;
       while(1)
       {


       cout<< "\n\n .........PASSWORD ENCRYPTION AND DECRYPTION MAIN MENU...........\n\n";
       cout<<" \n\n  PRESS 1 FOR ENCRYPTION.....\n\n";
       cout<<" \n\n  PRESS 2 FOR DECRYPTION.....\n\n";
       cout<<" \n\n  PRESS 3 TO EXIT............\n\n";
       cout<<" \n\n  PLEASE NOTE THAT THE ORIGINAL AND ENCRYPTED PASSWORDS ARE CASE SENSITIVE \n\n ";
       cout<<" \n\n\n ENTER YOUR CHOICE : \a\b\b ";
       cin >> choice;

         switch(choice)
          {
            case 1:  a1.Encryption();
                     break;
            case 2:  a1.Decryption();
                     break;
            case 3: exit(0);
            default:
                cout << "\n\n SORRY!!! WRONG CHOICE!!!!\a\a\a\a\a\n\n";
         }

       }

  return 0;


}




