#include "utilities.h"

/**
* @file utilities.c
* @brief Funções auxiliares da interface;
*/


/** @brief Função que retorna um utilizador da hashtable a partir do seu id;
*
* @param ht     	Apontador para a tabela de Hash(GHashTable*);
* @param id      	Identificador do utilizador;     
* @return User    	O apontador da estrutura User contido na tabela de hash;
*
*/

User get_User (GHashTable* ht,long id) {
	return g_hash_table_lookup(ht,GINT_TO_POINTER((glong) id));
}

/** @brief Função que retorna um post da hashtable a partir do seu id;
*
* @param ht     	Apontador para a tabela de Hash(GHashTable*);
* @param id      	Identificador do post;     
* @return User    	O apontador da estrutura Post contido na tabela de hash;
*
*/

Post get_Post (GHashTable* hp,long id) {
	return g_hash_table_lookup(hp,GINT_TO_POINTER((glong) id));
}

/** @brief Função que retorna uma LONG_LIST dos identificadores de N utilizadores;
*
* @param list     		Apontador para a lista ligada(GList*) de utilizadores;
* @param func      		Função de comparação;     
* @param N 				Número pretendido de utilizadores;
* @return LONG_LIST    	O apontador da estrutura LONG_LIST com N utilizadores ordenados pela função fornecida;
*
*/

LONG_list sort_user_by_N (GList* list,GCompareFunc func,int N) {
	User u = NULL;
	LONG_list res = create_list(N);
	int count =0;
	long uid;
	list=g_list_sort(list,func);
	while(list!=NULL && count<N) {
		u = (User)list->data;
		uid = getIDUser(u);
		set_list(res,count,uid);
		count++;
		list=list->next;
	}
	return res;	
}

/** @brief Função que retorna uma LONG_LIST dos identificadores de N posts;
*
* @param list     		Apontador para a lista ligada(GList*) de posts;
* @param func      		Função de comparação;     
* @param N 				Número pretendido de posts;
* @return LONG_LIST    	O apontador da estrutura LONG_LIST com N posts ordenados pela função fornecida;
*
*/

LONG_list sort_post_by_N (GList* list,GCompareFunc func,int N) {
	Post p = NULL;
	LONG_list res = create_list(N);
	int count =0;
	list=g_list_sort(list,func);
	while(list!=NULL && count<N) {
		p = (Post)list->data;
		set_list(res,count,getID(p));
		count++;
		list=list->next;
	}
	return res;
}

/** @brief Função que retorna a contagem de perguntas e respostas sobre a forma de um LONG_pair;
*
* @param list     			Apontador para a lista ligada(GList*) de posts;
* @param begin      		Data inicial;     
* @param end 				Data final;
* @return LONG_pair    		O apontador da estrutura LONG_pair com a contagem de perguntas e respostas;
*
*/

LONG_pair total_QandA(GList* list,Date begin, Date end) {
	LONG_pair lp;
	Post p=NULL;
	Date d=NULL;
	long answercount,questioncount;
	answercount=questioncount=0;
	while(list!=NULL) {
		p = (Post)list->data;
		d = get_DDate(p);	
		if (betweenDate (d,begin,end)) {
			if (isQuestion(p)) questioncount+=1;
			if (isAnswer(p)) answercount+=1;
		}
		list=list->next;
	}
	lp = create_long_pair(questioncount,answercount);
	return lp;
}

/** @brief Função que retorna a lista ligada de respostas contidas no intervalo de tempo especificado;
*
* @param list     			Apontador para a lista ligada(GList*) de posts;
* @param begin      		Data inicial;     
* @param end 				Data final;
* @return GList*    		O apontador da estrutura GList com a lista ligada de posts feitos entre o intervalo de tempo especificado;
*
*/

GList* filter_answer_by_dates(GList* list,Date begin,Date end) {
	Post p = NULL;
	Date d = NULL;
	GList* aux = NULL;
	while (list!=NULL) {
		p = (Post) list->data;
		d = get_DDate(p);
		if (isAnswer(p) && betweenDate (d,begin,end)) aux = g_list_insert_sorted(aux,(gpointer) p,(GCompareFunc) cmpPostScore);
			list=list->next;
	}
	return aux;
}

/** @brief Função que retorna a lista ligada de perguntas contidas no intervalo de tempo especificado;
*
* @param list     			Apontador para a lista ligada(GList*) de posts;
* @param begin      		Data inicial;     
* @param end 				Data final;
* @return GList*    		O apontador da estrutura GList com a lista ligada de posts feitos entre o intervalo de tempo especificado;
*
*/

GList* filter_questions_by_dates(GList* list,Date begin,Date end) {
	Post p = NULL;
	Date d = NULL;
	GList* aux = NULL;
	while (list!=NULL) {
		p = (Post) list->data;
		d = get_DDate(p);
		if(isQuestion(p) && betweenDate (d,begin,end) )aux = g_list_insert_sorted(aux,(gpointer) p,(GCompareFunc) cmpAnswerCount);
		list=list->next;
	}
	return aux;
}

/** @brief Função que retorna a uma LONG_LIST com N identificadores de posts;
*
* @param list     			Apontador para a lista ligada(GList*) de posts;
* @param  N      			Dimensão da lista;     
* @return LONG_list    		O apontador da estrutura LONG_list com os identificadores de N posts;
*
*/

LONG_list set_long_N (GList* list,int N) {
	int i;
	long pid;
	Post p = NULL;
	LONG_list res = create_list(N);
	for (i=0;i<N && list!=NULL;i++,list=list->next) {
			p = (Post)list->data;
			pid = getID(p);
			set_list(res,i,pid);
	}
	return res;
}

/** @brief Função que retorna um STR_pair que contem o titulo de uma pergunta e o nome do utilizador;
*
* @param  ht     			Apontador para a lista ligada(GList*) de posts;
* @param  p      			Apontador para a estrutura Posts;
* @param  u     			Apontador para a estrutura Users;
* @return STR_pair    		O apontador da estrutura STR_pair com o titulo da pergunta e nome do autor;
*
*/

STR_pair infos_from (GHashTable* ht,Post p,User u) {
	STR_pair new;
	long pid;
	if (isAnswer(p)) {
		pid = getParentID(p);
		p = get_Post(ht,pid);
	}
	char* title = getTitle(p);
	char* name = getDisplayName(u);
	new=create_str_pair(title,name);
	return new;
}

/** @brief Função que retorna a contagem de perguntas e respostas sobre a forma de um LONG_pair;
*
* @param list     			Apontador para a lista ligada(GList*) de posts;
* @param word      			String de procura;     
* @return GList*   			O apontador da estrutura GList com a lista ligada de posts que contêm a word no titulo,ordenados por cronologia inversa;
*
*/

GList* filter_question_inTitle(GList* list,char* word) {
	Post p = NULL;
	GList* aux = NULL;
	char* buff;
	list = g_list_sort(list,(GCompareFunc) cmpDate);
	while (list!=NULL) {
		p = (Post) list->data;
		buff = getTitle(p);
		if (isQuestion(p) && inTitle(buff,word)) aux = g_list_append(aux,(gpointer) p);
		list=list->next;
	}
	return aux;
}

/** @brief Função que retorna a lista ligada de posts feitos entre um dado intervalo de tempo que contenham uma determinada tag;
*
* @param list     			Apontador para a lista ligada(GList*) de posts;
* @param tag      			Tag de procura;
* @param begin 				Data inicial;
* @param end 				Data final;     
* @return GList*    		O apontador da estrutura GList com a lista ligada de posts,feitos no intervalo de tempo pedido,que contêm a tag especificada;
*
*/

GList* filter_question_tags_date(GList* list,char* tag,Date begin,Date end) {
	Post p = NULL;
	Date d = NULL;
	GList* aux = NULL;
	char* tagz;
	while (list!=NULL) {
		p = (Post) list->data;
		d = get_DDate(p);
		if (isQuestion(p) && betweenDate (d,begin,end)) {
			tagz=mystrdup(getTags(p));
			if (inTag(tagz,tag)) aux = g_list_insert_sorted(aux,(gpointer) p,(GCompareFunc) cmpDate);
		}
		list=list->next;
	}
	return aux;
}

/** @brief Função que retorna a lista ligada de posts ordenados por cronologia inversa;
*
* @param list     			Apontador para a lista ligada(GList*) de posts;     
* @return GList*    		O apontador da estrutura GList com a lista ligada de posts ordenados por cronologia inversa;
*
*/

GList* filter_ordered_posts(GList* list) {
	Post p = NULL;
	GList* aux = NULL;
	while (list!=NULL) {
		p = (Post) list->data;
		aux = g_list_insert_sorted(aux,(gpointer) p,(GCompareFunc) cmpDate);
		list = list->next;
	}
	return aux;
}

/** @brief Função que retorna um array com os identificadores de 10 posts;
*
* @param list     			Apontador para a lista ligada(GList*) de posts;     
* @return long*    			Um array com os identificadores de 10 posts;
*
*/

long* get_10_latest(GList* list) {
	int i;
	long pid;
	Post p = NULL;
	long* l = malloc(sizeof(long)*10);
	for (i=0;i<10 && list!=NULL;i++,list=list->next) {
		p = (Post)list->data;
		pid = getID(p);
		l[i]=pid;
	}
	return l;
}

/** @brief Função que retorna a lista ligada de respostas referentes a uma certa pergunta;
*
* @param l     				Apontador para a lista ligada(GList*) de posts;
* @param postid      		Identificador da pergunta;     
* @return GList*    		O apontador da estrutura GList com a lista ligada de respostas da pergunta especificada;
*
*/

GList* get_Answers(GList* l,long postid) {
	Post p = NULL;
	GList* res = NULL;
	while (l!=NULL) {
		p = (Post) l->data;
		if (isAnswer(p) && getParentID(p)==postid) res = g_list_prepend(res,(gpointer) p);
		l=l->next;
	}
	return res;
}

/** @brief Função que verifica se um certo utilizador respondeu a uma pergunta;
*
* @param list     			Apontador para a lista ligada(GList*) de posts;
* @param postid      		Identificador da pergunta;
* @param uid 				Identificador do utilizador;     
* @return int    		 	1 caso se verifique, 0 caso contrário;
*
*/

int has_answered_post(GList* list,long postid,long uid) {
	GList* res = get_Answers(list,postid);
	Post p = NULL; 
	int r=0;
	while (res!=NULL) {
		p = (Post) res->data;
		if (getOwnerID(p)==uid) r=1;
		res=res->next;
	}
	return r;
}

/**  @brief Função que retorna uma LONG_LIST que contêm os identificadores de N posts que ambos os utilizadores tenham contribuido;
*
* @param list     			Apontador para a lista ligada(GList*) de posts "original" ;
* @param aux 				Apontador para a lista ligada(GList*) de posts que ambos fizeram;
* @param id1      			Identificador do primeiro utilizador;
* @param id2 				Identificador do segundo utilizador;
* @param N  				Dimensão da lista;     
* @return LONG_list    		O apontador da estrutura LONG_list com os N posts em que ambos os utilizadore contribuiram;
*
*/

LONG_list filter_both_contributions(GList* com,GList* aux, long id1,long id2,int N) {
	int i=0;
	long oid,pid;
	Post p = NULL;
	LONG_list res = create_list(N);
	GList* posts1 = posts_from(com,id1);
	GList* posts2 = posts_from(com,id2);
	while(aux!=NULL && i<N) {
		p = (Post)aux->data;
		oid = getOwnerID(p);
		if (isQuestion(p)) {
			pid = getID(p);
			if (oid==id1 && has_answered_post(posts2,pid,id2)) {
				set_list(res,i,pid);
				i++;
			} 
			else if (oid==id2 && has_answered_post(posts1,pid,id1)) {
				set_list(res,i,pid);
				i++;
			} 
		}
		if (isAnswer(p)) {
			pid = getParentID(p);
			if (oid == id1 && has_answered_post(posts2,pid,id2))  {
				set_list(res,i,pid);
				i++;
				}
			}
		aux=aux->next;	
	}
	return res;
}

/** @brief Função que retorna a lista ligada de posts feitos por um utilizador;
*
* @param list     			Apontador para a lista ligada(GList*) de posts;
* @param id      			Identificador do utilizador     
* @return GList*    		O apontador da estrutura GList com a lista ligada de posts feitos pelo utilizador especificado;
*
*/

GList* posts_from (GList* list,long id) {
	GList* aux = NULL;
	Post p = NULL;
	while(list!=NULL) { 
		p = (Post) list->data;
		if (getOwnerID(p)==id) aux = g_list_prepend(aux,(gpointer) p);
		list=list->next;
	}
	return aux;
}

/** @brief Função que retorna a lista ligada de posts feitos por dois utilizadores;
*
* @param list     			Apontador para a lista ligada(GList*) de posts;
* @param id1      			Identificador do primeiro utilizador;
* @param id2				Identificador do segundo utilizador;     
* @return GList*    		O apontador da estrutura GList com a lista ligada de posts feitos pelos dois utilizadores;
*
*/

GList* posts_from_both (GList* list,long id1,long id2) {
	GList* aux = NULL;
	Post p = NULL;
	while(list!=NULL) { 
		p = (Post) list->data;
		if (getOwnerID(p)==id1 || getOwnerID(p)==id2) aux = g_list_prepend(aux,(gpointer) p);
		list=list->next;
	}
	return aux;
}

/** @brief Função que retorna a lista ligada de respostas de uma pergunta específica;
*
* @param list     			Apontador para a lista ligada(GList*) de posts;
* @param id      			Identificador da pergunta;     
* @return GList*    		O apontador da estrutura GList com a lista ligada de respostas da pergunta especificada;
*
*/

GList* filter_answers_by_qid (GList* list,long id) {
	Post p1 = NULL;
	GList* aux = NULL;
	while (list!=NULL) {
		p1 = (Post)list->data;
		if(isAnswer(p1) && getParentID(p1)==id) aux = g_list_prepend(aux,(gpointer) p1);
		list=list->next;
	}
	return aux;
}

/** @brief Função que retorna a lista ligada de posts feitos por um certo utilizador num intervalo de tempo definido;
*
* @param posts     			Apontador para a lista ligada(GList*) de posts;
* @param uid      			Identificador do utilizador;
* @param x 					Data inicial;
* @param y 					Data final; 
* @return GList*    		O apontador da estrutura GList com a lista ligada de posts feitos pelo utilizador especificado no intervalo de tempo;
*
*/

GList* filter_by_user_and_dates (GList* posts,long uid,Date x, Date y) {
	GList* res = NULL;
	Date d = NULL;
	Post p = NULL;
	long oid;
	while(posts!=NULL) {
		p = (Post) posts->data;
		oid = getOwnerID(p);
		d = get_DDate(p);
		if (oid==uid && betweenDate(d,x,y)) {
			if (isQuestion(p)) res = g_list_prepend(res,(gpointer) p);
		} 
		posts=posts->next;	
	}
	return res;
}

/** @brief Função que incrementa os contadores das tags presentes num post;
*
* @param tags     			Apontador para a lista ligada(GList*) de tags;
* @param p      			Apontador para a estrutura Posts;     
*/

void set_Tag_Count (GList* tags,Post p) {
	Tag t=NULL;
	char* name=NULL;
	char* res = getTags(p);
	while (tags!=NULL) {
		t = (Tag) tags->data;	
		name = getTagName(t);
		if (inTag(res,name)) add_Tag_Count(t);
		tags = tags->next;
	}
}

/** @brief Função que aplica a fórmula de cálculo da melhor resposta;
*
* @param p     			Apontador para a estrutura Posts;
* @param u      		Apontador para a estrutura Users;     
* @return int    		Resultado da aplicação da fórmula;
*
*/

int calc_answer (Post p,User u) {
	int rep,comt,score,res;
	rep = getRep(u);
	comt = getCommentCount(p);
	score = getScore(p);
	res = ((0.65*score)+(0.25*rep)+(0.1*comt));
	return res;
}

/** @brief Função que retorna o cálculo da melhor resposta de um post;
*
* @param com     			Apontador para a hashtable (GHashTable*) de utilizadores;
* @param aux      			Apontador para a lista ligada(GList*) de posts;     
* @return long    			Identificador da melhor resposta;
*
*/

long calculate_best_answer(GHashTable* com,GList* aux) {
	Post p1 = NULL;
	User u = NULL;
	long idr=0;
	int curr,max,oid;
	curr=max=0;
	while (aux!=NULL) {
		p1 = (Post)aux->data;
		oid = getOwnerID(p1);
		u = get_User(com,oid);
		curr = calc_answer(p1,u);
		if (curr>max) {
			max = curr;
			idr = getID(p1);
		}
		aux = aux->next;
	}
	return idr;
}

/** @brief Função que retorna uma LONG_LIST de N tags;
*
* @param list     			Apontador para a lista ligada(GList*) de tags;
* @param func      			Função de comparação;     
* @return LONG_LIST    		O apontador da estrutura LONG_LIST que contém os N identificadores de uma tag ordenados pela função func;
*
*/

LONG_list sort_N_tags_by (GList* tags,GCompareFunc func,int N){
	LONG_list res = create_list(N);
	Tag t = NULL;
	long tid;
	int i=0;
	tags = g_list_sort(tags,func);
	while(tags!=NULL && i<N) {
		t = (Tag) tags->data;
		tid = getTagID(t);
		set_list(res,i,tid);
		i++;
		tags = tags->next;	
	}
	return res;
}

/** @brief Função que incrementa os contadores das tags presentes em cada um dos posts;
*
* @param list     			Apontador para a lista ligada(GList*) de posts;
* @param com      			Apontador para a lista ligada(GList*) de tags;     
* 
*/

void set_Tag_Counters (GList* totalposts,GList* com) {
	Post p = NULL;
	while (totalposts!=NULL) {
		p = (Post) totalposts->data;
		set_Tag_Count (com,p);
		totalposts=totalposts->next;
	}
}

/** @brief Função que retorna a lista ligada dos N melhores utilizadores;
*
* @param users     			Apontador para a lista ligada(GList*) de utilizadores;
* @param N      			Número de utilizadores;     
* @return GList*    		O apontador da estrutura GList com a lista ligada dos N melhores utilizadores;
*
*/

GList* create_N_best_users(GList* users,int N) {
	GList* nbest = NULL;
	User u = NULL;
	int i=0;
	users = g_list_sort(users,(GCompareFunc) cmpRep);
	while (users!=NULL && i<N) {
		u = (User) users->data;
		nbest = g_list_append(nbest,(gpointer) u);
		i++;
		users=users->next;
	}
	return nbest;
}

/** @brief Função que retorna a lista ligada de todos os posts feitos pelos N melhores utilizados efetuados dentro de um intervalo de tempo;
*
* @param nbest     			Apontador para a lista ligada(GList*) de utilizadores;
* @param com      			Apontador para a lista ligada(GList*) de posts;
* @param begin				Data inicial;
* @param end				Data final;     
* @return GList*    		O apontador da estrutura GList com a lista ligada de posts feitos pelos N melhores utilizadores,no intervalo de tempo especificado;
*
*/

GList* filter_total_posts (GList* nbest,GList* com,Date begin,Date end) {
	GList* filter = NULL;
	GList* totalposts = NULL;
	User u = NULL;
	long uid;
	while(nbest!=NULL) {
		u = (User) nbest->data;
		uid = getIDUser(u);
		filter = filter_by_user_and_dates(com,uid,begin,end);
		totalposts = g_list_concat(totalposts,filter);
		nbest = nbest->next;
	}
	return totalposts;
}