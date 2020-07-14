////////////////////////////////
/// Inclusão das bibliotecas ///
////////////////////////////////
#include <string>
#include <iostream>

// Se estiver rodando no windows
// precisamos incluir a biblioteca
// de modo diferente
#ifdef __WIN32
	#include <mysql.h>
#else
	// Em outros sistemas, creio eu,
	// é desse outro jeito
	#include <mysql/mysql.h>
#endif

///////////////////
/// Protótipos ////
///////////////////
void exibeMenu(); 
void desconectar();
void verCompromissos();
void mostrarErroDoMysql();
void adicionarCompromisso();

/////////////////////////////
/// Variáveis globais X<( ///
/////////////////////////////

/**
 * Contém a conexão com o banco de dados
 */
MYSQL *connexao;
bool conectado = false;

//////////////////
/// Constantes ///
//////////////////

const unsigned int ADICIONAR_COMPROMISSO = 0;
const unsigned int REMOVER_COMPROMISSO = 1;
const unsigned int MOSTRAR_COMPROMISSO = 2;
const unsigned int EDITAR_COMPROMISSO = 3;
const unsigned int SAIR = 4;

/**
 * Função principal
 */
int main(int argc, char **argv) {

	// Exibe a mensagem de boas vindas
	std::cout << "Boas vindas da agenda!" << std::endl;

	exibeMenu();

	// Guarda a opção escolhida
	int opcao;

	// Entra em um loop infinito perguntando
	// o que o usuário deseja fazer
	while (true) {

		// Pergunta a opção do usuário
		std::cin >> opcao;

		// Executa a ação escolhida
		switch (opcao) {
			case ADICIONAR_COMPROMISSO:
				adicionarCompromisso();
				break;
			case REMOVER_COMPROMISSO:
				// TODO implementar
				std::cout << "Falta implementar." << std::endl;
				break;
			case MOSTRAR_COMPROMISSO:
				verCompromissos();
				break;
			case EDITAR_COMPROMISSO:
				// TODO implementar
				std::cout << "Falta implementar." << std::endl;
				break;
		}

		// Exibe o menu novamente
		exibeMenu();
	}

	desconectar();
	return 0;
}

/**
 * Exibe um menu para o usuário
 */
void exibeMenu() {
	std::cout << "Escolha uma opção:" << std::endl;
	std::cout << ADICIONAR_COMPROMISSO << " - Adicionar compromisso" << std::endl;
	std::cout << REMOVER_COMPROMISSO << " - Remover compromisso" << std::endl;
	std::cout << MOSTRAR_COMPROMISSO << " - Mostrar compromisso" << std::endl;
	std::cout << EDITAR_COMPROMISSO << " - Editar compromisso" << std::endl;
	std::cout << SAIR << " - SAIR" << std::endl;
}

/**
 * Mostra os erros que podem ocorrer na conexão
 * @param mysql
 */
void mostrarErroDoMysql(MYSQL *mysql) {
	printf("Erro: (%d) [%s] \"%s\"", mysql_errno(mysql), mysql_sqlstate(mysql), mysql_error(mysql));
	mysql_close(mysql);
	exit(-1);
}

/**
 * Conecta no banco de dados
 * @return - true: Conectou, false: Falha ao conectar
 */
bool conectar() {

	if (conectado) return true;

	connexao = mysql_init(NULL);
	if (!mysql_real_connect(connexao, "127.0.0.1", "root", "1234", "Agenda", 3306, NULL, 0)) {
		mostrarErroDoMysql(connexao);

		conectado = false;
		return false;
	}

	conectado = true;
	return true;
}

/**
 * Desconecta do banco de dados
 */
void desconectar() {
	mysql_close(connexao);
	conectado = false;
}

/**
 * Adiciona um compromisso
 */
void adicionarCompromisso() {

	// Verifica se a conexÃ£o foi realizada com sucesso
	if (!conectar()) {
		std::cout << "Falha ao conectar ao banco de dados!" << std::endl;
		return;
	}

	// VariÃ¡veis usadas para montar o query
	std::string dia, mes, ano, descricao;

	// Solicita o dia do compromisso
	std::cout << "Informe o dia:";
	std::cin >> dia;

	// Solicita o mês do compromisso
	std::cout << "Informe o mês:";
	std::cin >> mes;

	// Solicita o ano do compromisso
	std::cout << "Informe o ano:";
	std::cin >> ano;

	// Solicita a descrição do compromisso
	std::cout << "Descreva o compromisso:";
	std::cin >> descricao;

	// Monta a query
	std::string sql = "insert into Compromisso (data, descricao)values('" + ano + "-" + mes + "-" + dia + "','" + descricao + "')";

	// Executa a query
	int statusDeExecucao = mysql_query(connexao, sql.data());

	// Verifica se deu tudo certo
	if (statusDeExecucao == 0) {
		// Deu certo!
		std::cout << "Compromisso inserido" << std::endl;
	} else {
		// Algo deu errado!
		mostrarErroDoMysql(connexao);
		std::cout << "Falha ao inserir compromisso!" << std::endl;
	}

}

void verCompromissos() {
}

void editarCompromisso() {
    
	std::string descricao, mes, ano, cod, dia;
	char cont;

	Compromissos();

	std::cout << "Digite o codigo do compromisso: ";
	std::cin >> cod;

	std::cout << "Informe o dia do compromisso: ";
	std::cin >> dia;

	std::cout << "Informe o mês do compromisso: ";
	std::cin >> mes;

	std::cout << "Informe o ano do compromisso: ";
	std::cin >> ano;

	std::cout << "Insira a descrição do compromisso: ";
	std::cin >> descricao;

	std::string sql = "UPDATE Compromisso SET data='" + ano + "-" + mes + "-" + dia + ", descricao='" + descricao + "' WHERE cod='" + cod + "'";

    std::cout << "Digite 'm' para alterar compromisso (as configurações anteriores não serão salvas): ";

    std:cin >> cont;

    if(cont == 'm') {

		int statusDeExecucao = mysql_query(connexao, sql.data());
		if (statusDeExecucao == 0) {
		std::cout << "Compromisso modificado!" << std::endl;
		} 
		else {
			mostrarErroDoMysql(connexao);
			std::cout << "O compromisso não foi alterado" << std::endl;
		}
    }
    else
    	return;
}
}
