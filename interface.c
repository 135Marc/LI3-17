#include "interface.h"


typedef struct TCD_community {
	GHashTable* hashUser;
	GHashTable* hashPost;
	GHashTable* hashTags;
}TCD_community;


/**	@brief Função que inicializa a estrutura
*	@return TAD_community
*/
TAD_community init (TAD_community ht) {
	ht = g_new(TCD_community,1);
	ht->hashUser = g_hash_table_new_full((GHashFunc) g_direct_hash,(GEqualFunc) g_direct_equal,NULL,(GDestroyNotify) freeUser);
	ht->hashPost = g_hash_table_new_full((GHashFunc) g_direct_hash,(GEqualFunc) g_direct_equal,NULL,(GDestroyNotify) freePost);
	ht->hashTags = g_hash_table_new_full((GHashFunc) g_direct_hash,(GEqualFunc) g_direct_equal,NULL,(GDestroyNotify) freeTag);
	return ht;
}


/**	@brief Função que retorna o apontador para a tabela de Hash dos posts
*   @param TAD_community
*	@return GHashTable*
*/
GHashTable* get_HashT_Posts (TAD_community ht) {
	return ht->hashPost;
}


/**	@brief Função que retorna o apontador para a tabela de Hash dos users
*	@param TAD_community
*	@return GHashTable*
*/
GHashTable* get_HashT_Users (TAD_community ht) {
	return ht->hashUser;
}


/**	@brief Função que retorna o apontador para a tabela de Hash das tags
*	@param TAD_community
*	@return GHashTable*
*/
GHashTable* get_HashT_Tags (TAD_community ht) {
	return ht->hashTags;
}


/**	@brief Função que retorna os users em forma de lista ligada
*	@param TAD_community
*	@return GList*
*/
GList* get_Users (TAD_community ht) {
	return g_hash_table_get_values(ht->hashUser);
}


/**	@brief Função que retorna os post em forma de lista ligada
*	@param TAD_community
*	@return GList*
*/
GList* get_Posts (TAD_community hp) {
	return g_hash_table_get_values(hp->hashPost); 
}


/**	@brief Função que retorna os tags em forma de lista ligada
*	@param TAD_community
*	@return GList*
*/
GList* get_Tags (TAD_community ht) {
	return g_hash_table_get_values(ht->hashTags);
}


/**	@brief Função que faz o load dos ficheiros XML para as tabelas de Hash
*	@param TAD_community
*	@param char* path para o ficheiro XML
*	@return TAD_community
*/
TAD_community load (TAD_community com, char* dump_path) {
	com->hashUser = load_user(com->hashUser,dump_path);
	com->hashPost = load_post(com->hashPost,com->hashUser,dump_path);
	com->hashTags = load_tag(com->hashTags,dump_path);
	return com;
}


/**	@brief Função que retorna o titulo e o nome do utilizador do autor do post
*	@param TAD_community
*	@param long ID
*	@return STR_pair
*/
// QUERY 1
STR_pair info_from_post(TAD_community hp, long id) {
	GHashTable* htp = get_HashT_Posts(hp);
	GHashTable* htu = get_HashT_Users(hp);
	Post p = get_Post(htp,id);
 	long uid=getOwnerID(p);
	User u = get_User(htu,uid);
	STR_pair new = infos_from(htp,p,u);
	return new;
}


/**	@brief Função que retorna os identificadores dos n utilizadores com o maior numero de posts
*	@param TAD_community
*	@param int n
*	@return LONG_list 
*/
// QUERY 2
LONG_list top_most_active(TAD_community com, int N) {
	GList* usa = get_Users(com);
	LONG_list res = sort_user_by_N (usa,(GCompareFunc) cmpPostCount,N);
	g_list_free(usa);
	return res;
}


/**	@brief Função que retorna o numero total de posts entre duas datas, com as perguntas e respostas identificadas separadamente
*	@param TAD_community
*	@param Date inicio
*	@param Date fim
*	@return LONG_pair perguntas e respostas
*/
// QUERY 3
LONG_pair total_posts(TAD_community com, Date begin, Date end) {
	GList* res = get_Posts(com);
	LONG_pair lp = total_QandA(res,begin,end);
	g_list_free(res);
	return lp;
}


/**	@brief Função que retorna uma lista com os identificadores de todas as perguntas que contém uma determinada tag
*	@param TAD_community
*	@param char* tag
*	@param Date inicio
*	@param Date fim
*	@return LONG_list lista com os ID's das perguntas com uma determinada tag, entre uma data e ordenada por cronologia inversa
*/
//QUERY 4
LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end) {
	GList* posts = get_Posts(com);
	GList* filtered = filter_question_tags_date(posts,tag,begin,end);
	int i = (int) g_list_length(filtered);
	LONG_list res = sort_post_by_N (filtered,(GCompareFunc) cmpDate,i);
	g_list_free(filtered);
	g_list_free(posts);
	return res;
}


/**	@brief Função que retorna a informação do perfil de um utilizador (short bio) e os ID's dos seus 10 últimos posts (ordem inversa)
*	@param TAD_community
*	@param long ID
*	@return USER estrutura dada pela equipa docente que contem a shortbio e os ID's dos 10 posts
*/
// QUERY 5
USER get_user_info(TAD_community com, long id) {
	GHashTable* htu = get_HashT_Users(com);
	GList* posts = get_Posts(com);
	User u = get_User(htu,id);
	GList* filter= posts_from (posts,id);
	GList* aux = filter_ordered_posts(filter);
	char* shortbio = getShortBio(u);
	long *l = get_10_latest(aux);
	USER res = create_user(shortbio,l);
	g_list_free(aux);
	g_list_free(filter);
	g_list_free(posts);
	return res;
}


/**	@brief Função que retorna os identificadores das respostas com mais votos, em ordem decrescente do score e entre duas datas
*	@param TAD_community
*	@param int N
*	@param Date inicio
*	@param Date fim
*	@return LONG_list lista com N elementos com as respostas com mais votos filtradas e ordenadas por ordem decrescente
*/
// QUERY 6
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end) {
	GList* posts = get_Posts(com);
	GList* filtered = filter_answer_by_dates(posts,begin,end);
	LONG_list res = set_long_N (filtered,N); 
	g_list_free(filtered);
	g_list_free(posts);
	return res;
}


/**	@brief Função que retorna os identificadores das perguntas com mais respostas, por ordem decrescente do número de respostas
*	@param TAD_community
*	@param int N
*	@param Date inicio
*	@param Date fim
*	@return LONG_list lista com N elementos com os ID's das perguntas com mais respostas, ordenado por ordem decrescente
*/
// QUERY 7
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end) {
	GList* posts = get_Posts(com);
	GList* aux = filter_questions_by_dates(posts,begin,end);
	LONG_list res= set_long_N (aux,N);
	g_list_free(aux);
	g_list_free(posts);
	return res;
}


/**	@brief Função que retorna uma lista com os identificadores das perguntas cujos os títulos a contenham, ordenadas por cronologia inversa
*	@param TAD_community
*	@param char* palavra
*	@param int N
*	@return LONG_list lista com N elementos com os ID's das perguntas cujo os titulos a contenham ordenado por ordem inversa
*/
// QUERY 8
LONG_list contains_word(TAD_community com, char* word, int N) {
	GList* posts = get_Posts(com);
	GList* aux = filter_question_inTitle(posts,word);
	LONG_list res = set_long_N(aux,N);
	g_list_free(aux);
	g_list_free(posts);
	return res;
}


/**	@brief Função que retorna os identificadores das últimas perguntas em que participaram dois utilizadores específicos, por cronologia inversa
*	@param TAD_community
*	@param long ID do utilizador 1
*	@param long ID do utilizador 2
*	@param int N
*	@return LONG_list
*/
//QUERY 9
LONG_list both_participated(TAD_community com, long id1, long id2, int N) {
	GList* posts = get_Posts(com);
	GList* aux = posts_from_both(posts,id1,id2);
	LONG_list res = filter_both_contributions(posts,aux,id1,id2,N);
	g_list_free(aux);
	g_list_free(posts);
	return res;
}


/**	@brief Função que retorna o identificador da melhor resposta
*	@param TAD_community
*	@param long ID
*	@return long ID da melhor resposta 
*/
// QUERY 10
long better_answer(TAD_community com, long id) {
	GHashTable* htp = get_HashT_Posts(com);
	GHashTable* htu = get_HashT_Users(com);
	Post p = get_Post(htp,id);
	if (getAnswerCount(p)==0) return -1;
	GList* list = get_Posts(com);
	GList* aux=filter_answers_by_qid(list,id);
	long best = calculate_best_answer(htu,aux);
	g_list_free(aux);
	g_list_free(list);
	return best;
}


/**	@brief Função que retorna os identificadores das tags mais usadas pelos utilizadores com melhor reputação, entre duas datas
*	@param TAD_community
*	@param int N
*	@param Date inicio
*	@param Date fim
*	@return LONG_list lista de tamanho N e com os ID's das tags mais usadas pelos melhores utilizadores
*/
//QUERY 11 
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end) {
	GList* users = get_Users(com);
	GList* posts = get_Posts(com);
	GList* tags = get_Tags(com);
	GList* nbest = create_N_best_users(users,N);
	GList* totalposts = filter_total_posts (nbest,posts,begin,end);
	set_Tag_Counters (totalposts,tags);
	LONG_list res = sort_N_tags_by (tags,(GCompareFunc) cmpCounter,N);
	g_list_free(nbest);
	g_list_free(users);
	g_list_free(totalposts);
	g_list_free(posts);
	g_list_free(tags);
	return res;
}


/**	@brief Função que lompa a estrutura
*	@param TAD_community
*	@return TAD_community 
*/
TAD_community clean (TAD_community hu) {
	 g_hash_table_destroy(hu->hashPost);
	 g_hash_table_destroy(hu->hashUser);
	 g_hash_table_destroy(hu->hashTags);
	 g_free(hu);
	 return hu;
}