#ifndef MESA_HPP
#define MESA_HPP
#include "tipos.hpp"

/**
 * @brief Representa uma mesa do restaurante e seu estado de ocupacao.
 *
 * Mantem a identificacao, o numero, a capacidade e o status operacional
 * da mesa.
 */
class Mesa {
private:
    int id;
    int numero;
    int capacidade;
    StatusMesa status;

public:
    /**
     * @brief Cria uma mesa com seus dados iniciais.
     * @param id Identificador unico da mesa.
     * @param numero Numero visivel da mesa no restaurante.
     * @param capacidade Quantidade maxima de pessoas que a mesa comporta.
     * @param status Estado inicial da mesa.
     */
    Mesa(const int id,const int numero,const int capacidade,const StatusMesa status);

    /** @brief Retorna o identificador da mesa. @return Identificador da mesa. */
    int getId() const;
    /** @brief Retorna o numero visivel da mesa. @return Numero da mesa. */
    int getNumero() const;
    /** @brief Retorna a capacidade de pessoas da mesa. @return Capacidade da mesa. */
    int getCapacidade() const;
    /** @brief Retorna o estado operacional da mesa. @return Status atual da mesa. */
    StatusMesa getStatus() const;

    /** @brief Atualiza o identificador da mesa. @param id Novo identificador. */
    void setId(const int id);
    /** @brief Atualiza o numero visivel da mesa. @param numero Novo numero da mesa. */
    void setNumero(const int numero);
    /** @brief Atualiza a capacidade de pessoas da mesa. @param capacidade Nova capacidade. */
    void setCapacidade(const int capacidade);
    /** @brief Atualiza o estado operacional da mesa. @param status Novo estado. */
    void setStatus(const StatusMesa status);

    /**
     * @brief Marca este objeto como ocupado.
     * @param Mesa Parametro da interface que nao e utilizado pela implementacao.
     */
    void ocupar(Mesa& Mesa);
    /**
     * @brief Marca este objeto como livre.
     * @param Mesa Parametro da interface que nao e utilizado pela implementacao.
     */
    void liberar(Mesa& Mesa);

};

#endif
