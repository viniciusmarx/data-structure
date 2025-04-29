# Sistema de Gerenciamento de Turmas, Alunos e Grupos

Este é um sistema simples em linguagem C para gerenciamento de turmas, alunos e grupos. O objetivo principal é permitir o cadastro, consulta e exclusão de turmas, bem como o gerenciamento de alunos associados e a criação de grupos de trabalho com base nessas turmas.

## Funcionalidades

-   ✅ Cadastrar turmas
-   ✅ Listar turmas existentes
-   ✅ Remover uma turma específica
-   ✅ Cadastrar alunos vinculados a uma turma
-   ✅ Listar alunos de uma turma
-   ✅ Criar grupos a partir dos alunos cadastrados em uma turma
-   ✅ Listar grupos criados
-   ✅ Incluir aluno em um grupo de uma turma
-   ✅ Remover aluno de um grupo de uma turma
-   ✅ Consultar alunos de grupos de uma turma
-   ✅ Listar alunos sem grupo em uma turma
-   ✅ Listar alunos que estão em mais de uma turma
-   ✅ Listar alunos que estão em apenas uma turma

## Como funciona

1. **Cadastro de Turmas**

    - O usuário informa um código para a nova turma.
    - A turma é armazenada em memória dinâmica e adicionada à lista de turmas.

2. **Listagem de Turmas**

    - Exibe todos os códigos das turmas cadastradas até o momento.

3. **Remoção de Turmas**

    - O usuário informa o código da turma a ser removida.
    - A turma e todos os dados associados (alunos e grupos) são removidos da memória.

4. **Cadastro de Alunos**

    - O usuário informa o código da turma e o nome do aluno.
    - O aluno é adicionado à lista da turma especificada.

5. **Listagem de Alunos**

    - Exibe os nomes dos alunos cadastrados em uma turma específica.

6. **Criação de Grupos**

    - O usuário informa o código da turma e o número de grupos desejados.
    - Os alunos são distribuídos de forma equilibrada entre os grupos.

7. **Listagem de Grupos**

    - Exibe todos os grupos formados dentro de uma turma, junto com os nomes dos alunos de cada grupo.

8. **Incluir Aluno em um Grupo**

    - O usuário informa o código da turma, o código do grupo e o código do aluno.
    - O aluno é adicionado ao grupo especificado dentro da turma.

9. **Remover Aluno de um Grupo**

    - O usuário informa o código da turma, o código do grupo e o código do aluno.
    - O aluno é removido do grupo especificado dentro da turma.

10. **Consultar Alunos dos Grupos**

    - Exibe todos os alunos de todos os grupos dentro de uma turma.

11. **Listar Alunos sem Grupo**

    - Exibe os alunos de uma turma que não estão alocados a nenhum grupo.

12. **Listar Alunos em Mais de Uma Turma**

    - Exibe os alunos que estão matriculados em mais de uma turma.

13. **Listar Alunos em Apenas Uma Turma**

    - Exibe os alunos que estão matriculados em apenas uma turma.

## Estrutura de Dados

-   Utiliza array para armazenar:
    -   Turmas
-   Utiliza listas encadeadas para armazenar:
    -   Alunos de cada turma
    -   Grupos dentro de cada turma

## Visualização da Estrutura

![Estrutura de dados](./structure.jpg)
