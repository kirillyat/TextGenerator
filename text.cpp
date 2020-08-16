//
// kirillyat
//
// 5 Aug 2020
//

#include <cstdio>
#include <cstdlib>

enum {
    NPREF = 2,
    NHASH = 4048,
    MAXGEN = 10000,
    MULTIPLIER = 31
};

struct Suffix {
    char *word;
    Suffix *next;
};

struct State {
    char *pref[NPREF];
    Suffix *suf;
    State *next;
};

State *StateHashTable[NHASH];


/* Вычисляет Хэш-код перфикса */
unsigned int hash(char *s[NPREF])
{
    unsigned int h = 0;
    unsigned char *p;

    for (int i = 0; i < NPREF; ++i) {
        for (p = (unsigned char *) s[i]; *p !='\0'; ++p) {
            h = (MULTIPLIER * h) + *p;
        }
    }
    return h % NHASH;
}


/* Ищет прификс в таблице и создает его по запросу */
State* lookup(char *prefix[NPREF], bool create)
{
    int i, h = hash(prefix);

    for (State st = StateHashTable[h]; st != NULL; st = st->next) {
        for (i = 0; i < NPREF; ++i)
            if (strcmp(prefix[i], st->pref[i]) != 0)
                break;
        if (i == NPREF)
            return st;
    }

    if (create) {
        st = new State;
        for (int i = 0; i < NPREF; ++i)
            st->pref[i] = prefix[i];
        st->suf = NULL;
        st->next = StateHashTable[h];
        StateHashTable[h] = sp;
    }
    return st;
}


/* Считывает входные данные и строит StateHashTable */
void build(char *prefix[NPREF], FILE *f)
{
    char buf[100], fmt[10];

    sprintf(fmt, "%%%ds", sizeof(buf)-1);
    while(fscanf(f, fmt, buf) != EOF)
      add(prefix, estrdup(buf));
}

/* Пополняет список суффиксов и обновлет StateHashTable */
void add(char *prefix[NPREF], char *suffix)
{
    State *st;

    st = lookup(prefix, true);
    addsuffix(st, suffix);
    /* сдвиг слов в префиксе */
    memmove(prefix, prefix+1, (NPREF-1)*sizeof(prefix[0]));
    prefix[NPREF-1] = suffix;
}






int main(int argc, char const *argv[]) {
    /* code */
    return 0;
}
