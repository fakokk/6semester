using System;
using System.Collections.Generic;

namespace Теория_автоматов_Л4
{
    public enum States { Begin, S, D, F, A, G, H, R, J, L, M}

    // класс состояние
    public class State
    {
        public States stateCurrent; // текущее состояние
        public States stateNext;    // следующее состояние
        public string value;        // обозреваемый символ

        public State()
        {
            stateCurrent = stateNext = States.Begin;
            value = "";
        }

        public State(States _stateCurrent, string _value, States _stateNext)
        {
            stateCurrent = _stateCurrent;
            value = _value;
            stateNext = _stateNext;
        }

        public State(State copyState)
        {
            stateCurrent = copyState.stateCurrent;
            stateNext = copyState.stateNext;
            value = copyState.value;
        }

        public static bool operator ==(State _state1, State _state2)
        {
            return _state1.value == _state2.value &&
                _state1.stateCurrent == _state2.stateCurrent &&
                _state1.stateNext == _state2.stateNext;
        }

        public static bool operator !=(State _state1, State _state2)
        {
            return _state1.value != _state2.value ||
                _state1.stateCurrent != _state2.stateCurrent ||
                _state1.stateNext != _state2.stateNext;
        }

    }





    internal class Program
    {

        // true - state есть в statesList
        // fasle - его там нет
        // logic hehe -_-
        public static bool ItemInsideList(List<State> statesList, State state)
        {
            for (int i = 0; i < statesList.Count; i++)
                if (state == statesList[i])
                    return true;
            return false;
        }

        // true - состояние недостижимо
        // fasle - состояние достижимо
        public static bool StateUnreachable(State state, List<State> finiteAutomaton)
        {
            for (int i = 0; i < finiteAutomaton.Count; i++)
            {
                if (state != finiteAutomaton[i] && state.stateCurrent == finiteAutomaton[i].stateNext ||
                state == finiteAutomaton[i] && state.stateCurrent == state.stateNext)
                    return false;
            }
            return true;
        }

        public static List<State> DeleteUnreachableStates(List<State> finiteAutomaton)
        {

            var states = new List<State>();
            states.Add(new State(finiteAutomaton[0]));


            for (int i = 1; i < finiteAutomaton.Count; i++)
            {
                if (ItemInsideList(states, finiteAutomaton[i]))
                    continue;

                if (StateUnreachable(finiteAutomaton[i], finiteAutomaton))
                    continue;

                states.Add(finiteAutomaton[i]);

            }

            return states;
        }

        public static List<State> DeleteExualStates(List<State> finiteAutomaton)
        {
            var states = new List<State>();
            states.Add(new State(finiteAutomaton[0]));
            for (int i = 1; i < finiteAutomaton.Count; i++)
            {
                //if (finiteAutomaton[i].stateCurrent == States.K && finiteAutomaton[i].stateNext == States.E)
                //    continue;
                if (ItemInsideList(states, finiteAutomaton[i]))
                    continue;
                if (StateUnreachable(finiteAutomaton[i], finiteAutomaton))
                    continue;
                states.Add(finiteAutomaton[i]);
            }
            return states;
        }


        // true - состояние есть в таблице, 
        // faslse - нет
        public static bool StateInTable(List<List<string>> table, string state)
        {
            for (int i = 0; i < table.Count; i++)
            {
                if (table[i][0] == state)
                    return true;
            }

            return false;
        }

        // true - терминал есть в таблице, 
        // faslse - нет
        public static bool TerminalInTable(List<List<string>> table, string terminal)
        {
            for (int i = 0; i < table[0].Count; i++)
            {
                if (table[0][i] == terminal)
                    return true;
            }

            return false;
        }

        public static int GetNumberRow(List<List<string>> table, string state)
        {
            for (int i = 0; i < table.Count; i++)
                if (table[i][0] == state)
                    return i;

            return -1;
        }

        public static int GetNumberCol(List<List<string>> table, string terminal)
        {
            for (int i = 0; i < table.Count; i++)
                if (table[0][i] == terminal)
                    return i;

            return -1;
        }

        static void Main()
        {
            Console.WriteLine("");

            Console.WriteLine("Теория автоматов.Лабораторная работа №4. Вариант №9");
            List<State> finiteAutomaton = new List<State>
            {
                new State(States.S, "@", States.D),
                new State(States.S, "-", States.A),

                new State(States.A, "c", States.J),

                new State(States.D, "e", States.F),

                new State(States.F, "n", States.G),

                new State(States.G, "!", States.L),

                new State(States.J, "n", States.H),

                new State(States.H, "!", States.R),

                new State(States.R, "c", States.G),
                new State(States.R, "-", States.L),

                new State(States.L, "c", States.H),
                new State(States.L, "-", States.R),

                new State(States.M, "c", States.R),
                new State(States.M, "n", States.L)
            };

            Console.WriteLine("Изначальный автомат:");
            for (int i = 0; i < finiteAutomaton.Count; i++)
            {
                Console.WriteLine($"{finiteAutomaton[i].stateCurrent} -> {finiteAutomaton[i].value}{finiteAutomaton[i].stateNext}");
            }


            finiteAutomaton = DeleteUnreachableStates(finiteAutomaton);

            Console.WriteLine("\nКонечный автомат после удаления недостижимых состояний:");
            for (int i = 0; i < finiteAutomaton.Count; i++)
                Console.WriteLine($"{finiteAutomaton[i].stateCurrent} -> {finiteAutomaton[i].value}{finiteAutomaton[i].stateNext}");

            Console.WriteLine("\nКонечный автомат после удаления эквивалентных состояний:");
            for (int i = 0; i < finiteAutomaton.Count; i++)
                Console.WriteLine($"{finiteAutomaton[i].stateCurrent} -> {finiteAutomaton[i].value}{finiteAutomaton[i].stateNext}");

            List<List<string>> table = new List<List<string>>();
            table.Add(new List<string>());
            table[0].Add(" ");
            int k = 1;
            for (int i = 0; i < finiteAutomaton.Count; i++)
            {
                if (!StateInTable(table, finiteAutomaton[i].stateCurrent.ToString()))
                {

                    table.Add(new List<string>());
                    table[k].Add(finiteAutomaton[i].stateCurrent.ToString());
                    k++;
                }

                if (!TerminalInTable(table, finiteAutomaton[i].value))
                    table[0].Add(finiteAutomaton[i].value);

            }

            for (int i = 1; i < table.Count; i++)
                while (table[i].Count < table[0].Count)
                    table[i].Add(" ");

            int row = 0, col = 0;
            for (int i = 0; i < finiteAutomaton.Count; i++)
            {
                row = GetNumberRow(table, finiteAutomaton[i].stateCurrent.ToString());
                col = GetNumberCol(table, finiteAutomaton[i].value);
                table[row][col] = finiteAutomaton[i].stateNext.ToString();
            }

            Console.WriteLine("\nКонечный автомат результат:");
            for (int i = 0; i < table.Count; i++)
            {
                for (int j = 0; j < table[i].Count; j++)
                {
                    Console.Write(" " + table[i][j] + " |");
                }
                Console.WriteLine();
            }

            /*Console.WriteLine("\nКонечный автомат результат:");
            for (int i = 0; i < finiteAutomaton.Count; i++)
                Console.WriteLine($"{finiteAutomaton[i].stateCurrent} -> {finiteAutomaton[i].value}{finiteAutomaton[i].stateNext}");*/

            //Console.ReadKey();
        }
    }

}