cmake_minimum_required(VERSION 3.17)
project(project_4)

set(CMAKE_CXX_STANDARD 14)

include_directories(., Automatons)
ADD_EXECUTABLE(project_4
        Lexer.cpp
        Token.cpp
        Automatons/RightParenAutomaton.cpp
        Automatons/FactsAutomaton.cpp
        Automatons/StringAutomaton.cpp
        Automatons/UndefinedAutomaton.cpp
        Automatons/RulesAutomaton.cpp
        Automatons/ColonDashAutomaton.cpp
        Automatons/LeftParenAutomaton.cpp
        Automatons/AddAutomaton.cpp
        Automatons/MultiplyAutomaton.cpp
        Automatons/Q_MarkAutomaton.cpp
        Automatons/IDAutomaton.cpp
        Automatons/SchemeAutomaton.cpp
        Automatons/QueriesAutomaton.cpp
        Automatons/CommentAutomaton.cpp
        Automatons/PeriodAutomaton.cpp
        Automatons/ColonAutomaton.cpp
        Automatons/CommaAutomaton.cpp
        Parser.cpp
        main.cpp
        Interpreter.h
        DataLogProgram.h
        Database.h
        Parser.h
        Automatons/StringAutomaton.h
        Automatons/QueriesAutomaton.h
        Automatons/SchemeAutomaton.h
        Automatons/LeftParenAutomaton.h
        Automatons/CommentAutomaton.h
        Automatons/ColonAutomaton.h
        Automatons/FactsAutomaton.h
        Automatons/Automaton.h
        Automatons/ColonDashAutomaton.h
        Automatons/PeriodAutomaton.h
        Automatons/CommaAutomaton.h
        Automatons/UndefinedAutomaton.h
        Automatons/Q_MarkAutomaton.h
        Automatons/MultiplyAutomaton.h
        Automatons/RulesAutomaton.h
        Automatons/IDAutomaton.h
        Automatons/RightParenAutomaton.h
        Automatons/AddAutomaton.h
        Lexer.h
        Token.h
)


