#ifndef CLIENTE_HPP
#define CLIENTE_HPP
#include <string>

/**
 * @brief Representa um cliente cadastrado no restaurante.
 *
 * Mantem os dados de identificacao e contato do cliente.
 */
class Cliente {
    private:
        int id;
        std::string nome;
        std::string telefone;
    
    public:
        /**
         * @brief Cria um cliente com identificador, nome e telefone.
         * @param id Identificador unico do cliente.
         * @param nome Nome do cliente.
         * @param telefone Telefone para contato.
         */
        Cliente(int id, const std::string& nome, const std::string& telefone);

        /** @brief Retorna o identificador do cliente. @return Identificador do cliente. */
        int getId() const;
        /** @brief Retorna o nome do cliente. @return Nome do cliente. */
        std::string getNome() const;
        /** @brief Retorna o telefone do cliente. @return Telefone do cliente. */
        std::string getTelefone() const;

        /** @brief Atualiza o nome do cliente. @param nome Novo nome. */
        void setNome(const std::string& nome);
        /** @brief Atualiza o telefone do cliente. @param telefone Novo telefone. */
        void setTelefone(const std::string& telefone);
};

#endif