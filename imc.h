#define HASH_SIZE 109


enum VARTYPE {
    VTCONST = 1,
    VTREG,
    VTIDENTIFIER,
    VTADDRESS
};

enum INSTYPE {
    ITBRANCH = 1,
    ITOP,
    ITCALL
};

/* Ok, this won't scale to architectures like i386, but thats not
 * the goal right now.
 */
#define MAX_COLOR 32
/*
#define IREG_SET 0
#define NREG_SET 1
#define SREG_SET 2
#define PREG_SET 3
#define MAXREG_SET 4

extern int color_map[IREG_SET][MAX_COLOR];
*/

typedef struct _SymReg {
    char * name;             /* Symbolic name */
    char * reg;              /* Real register */
    char * fmt;              /* I=Int (I%d,...), F=Float, S=String, P=PMC */
    enum VARTYPE type;
    char set;                /* Which register set/file it belongs to */
    int color;
    int first;
    int last;
    struct _SymReg * next;
} SymReg;

typedef struct _Instruction {
    char * fmt;            /* printf style format string for instruction */
    SymReg * r0;           /*   uses {r0-r3}->reg                        */
    SymReg * r1;
    SymReg * r2;
    SymReg * r3;
    int type;
} Instruction;



Instruction * emitb(Instruction *);
Instruction * emit(Instruction *);
void emit_flush();
void clear_tables();
SymReg * mk_symreg(const char *, char t);
SymReg * mk_ident(const char *, char t);
SymReg * mk_const(const char *, char t);
SymReg * mk_address(const char *);
Instruction * mk_instruction(const char *, SymReg *, SymReg *, SymReg *, SymReg *);
void store_symreg(SymReg * r);
SymReg * get_sym(const char * name);
void relop_to_op(int, char *);
void compute_du_chain(SymReg * r);
int interferes(SymReg * r0, SymReg * r1);
void color_graph(SymReg ** graph);
int map_colors(int x, SymReg ** graph, int colors[]);
SymReg ** compute_graph();


/* This should be common with Cola */
unsigned int         hash_str(const char * str);
char                *str_dup(const char *);
char                *str_cat(const char *, const char *);

