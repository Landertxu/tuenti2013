#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <set>
#include <cmath>
#include <map>


using namespace std;


string bin (int a)
{
  string ans = "";
  for (int i = 0; i < 8; i++)
  {
    ans = " " + ans;
    ans = char(a%2+'0') + ans;
    a/=2;
  }
  return ans;
}

int hex2dec (char c)
{
  if (c >= '0' and c <= '9')
    return c-'0';
  return c-'a'+10;
}

char int2hex (int c)
{
  if (c < 10) return c+'0';
  return c+'a'-10;
}

string hexa (int a)
{
  if (a < 0) a += 256;
  string ans = "";
  ans += int2hex(a/16);
  ans += int2hex(a%16);
  return ans;
}

int main()
{
  //first, obtain the image input with this java code:
  /*
   * private char int2char (int a)
        {
                if (a < 10)
                        return (char) (a+'0');
                return (char)(a-10+'a');
        }
        @Override
        public void onReceive(Context context, Intent intent) {
                Bundle extras = intent.getExtras();
            if (extras != null) {
                
                byte key []= extras.getByteArray("SIGNAL_INFO");
                char s [] = new char[2*key.length];
                for (int i = 0; i < key.length; i++)
                {
                        Byte b = new Byte(key[i]);
                        int c = b.intValue();
                        c += 256;
                        c %= 256;
                        s[i*2] = int2char(c/16);
                        s[i*2+1] = int2char(c%16);
                }
                String output = new String (s);
                
                for (int i = 0; i < 50; i++)
                {
                        if (i*1000 >= output.length()) continue;
                        System.out.println(output.substring(i*1000, min(output.length(),(i+1)*1000)));
                }
                //System.out.println("Empiezo: con byte "+((key[0]+256)%256));
                        //intent.putExtra(EXTRA_MESSAGE, message);
                        //startActivity(intent);
            }
        }
        private int min(int a, int b) {
                if (a<b) return a;
                return b;
        }
        */
  
  //then, access to it using logcat:
  //adb logcat > ~/programacion/tuenti/2013/log.out
  
  //with this code we obtain an image:
  /*
  ifstream fin;
  fin.open ("imagen4.in");
  string s;
  ofstream fout;
  fout.open("imagen4.jpg");
  string total = "";
  while (getline(fin, s))
  {
    total += s.substr(21);
  }
  
  s = total;
  for (int i = 0; i < s.size()/2; i++)
  {
    unsigned char c = hex2dec(s[i*2])*16+hex2dec(s[i*2+1]);
    fout << c;
  }
  */
  
  //This image contain the codes: 442, 84, 158, 1615, 2316
  //Access to the database with this java code:
  /*public void sendMessage(View view) {
                String selectionArgs[] = new String[1];
                selectionArgs[0] = new String("2316");
                Cursor dataCursor = getContentResolver().query(
                                Uri.parse("content://com.tuenti.lostchallenge.datamodel.provider.ContestProvider/contest"),   // The content URI of the words table
                            null,                        // The columns to return for each row
                            "key = ?",                    // Selection criteria
                            selectionArgs,                     // Selection criteria
                            null);                        // The sort order for the returned rows
                
                while (dataCursor.moveToNext()) {
                        System.out.println("-->"+dataCursor.getString(0));
                }
                
        }
  */
  
  //obtaining the keys: 4223, 416, 815, 158, 164
  
  int keys[5] = {4223, 416, 815, 158, 164};
  
  int band;
  cin >> band;
  cout << keys[band] << endl;
  
}