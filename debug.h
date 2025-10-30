#ifndef DEBUG_H
#define DEBUG_H

#define CHECK(a) cout << endl << a << endl; getchar()

#define CHECKARR(a, b, pad) cout << endl; for(int i = 0; i < b; i++) cout << setw(pad) << a[i]; cout << endl; getchar()

#endif 