#pragma once
#define DEBUG(ON,fmt,...) do { if (ON) fprintf (stderr, fmt, ##__VA_ARGS__); }while (0)
#define DISPLAY(ON,ARR,SIZE) if (ON){ for (int i = 0; i<(int)(SIZE); i++) fprintf(stderr, "%d ", (int)(ARR)[i]); fprintf(stderr, "\n");}
#define PAUSE(ON) if (ON) system("pause")
#define CERR(ON,STRING) if (ON) std::cerr<<STRING<<std::endl
