using System;
using System.Collections.Generic;

// Создаем класс, представляющий состояние автомата
public class State
{
    public char Name { get; set; } // Название состояния (S, A, B, C, D, E)
    public Dictionary<char, State> Transitions { get; set; } // Словарь переходов
    public bool IsFinal { get; set; } // Флаг, обозначающий, является ли состояние конечным

    public State(char name, bool isFinal)
    {
        Name = name;
        Transitions = new Dictionary<char, State>();
        IsFinal = isFinal;
    }
}

// Создаем класс, представляющий конечный автомат
public class Automaton
{
    private State initialState; // Начальное состояние автомата

    public Automaton()
    {
        //состояния автомата
        State s = new State('S', true);
        State a = new State('A', false);
        State b = new State('B', true);
        State c = new State('C', true);
        State d = new State('D', true);
        State e = new State('E', true);

        //переходы между состояниями
        s.Transitions.Add('0', s);
        s.Transitions.Add('1', b);
        s.Transitions.Add('E', e);

        a.Transitions.Add('0', a);
        a.Transitions.Add('1', b);
        a.Transitions.Add('B', b);

        b.Transitions.Add('0', c);
        b.Transitions.Add('1', d);

        c.Transitions.Add('0', c);

        d.Transitions.Add('1', d);

        e.Transitions.Add('0', e);
        e.Transitions.Add('1', e);

        //начальное состояние
        initialState = s;
    }

    //метод, реализующий работу автомата
    public void Run(string input)
    {
        State currentState = initialState;

        for (int i = 0; i < input.Length; i++)
        {
            //есть ли переход по символу из текущего состояния
            if (currentState.Transitions.ContainsKey(input[i]))
            {
                //выводим текущее состояние
                Console.Write(currentState.Name + " ");
                //переходим в новое
                currentState = currentState.Transitions[input[i]];
            }
            else
            {
                Console.WriteLine("");
                Console.WriteLine("Состояние " + currentState.Name + " -> Ошибка: нет перехода по символу " + i + " = " + input[i]);
                return;
            }
        }

        //выводим последнее состояние
        Console.Write(currentState.Name);
        Console.WriteLine("");

        //является ли текущее состояние конечным
        if (currentState.IsFinal)
        {
            Console.WriteLine("Цепочка " + input + " принята автоматом");
        }
        else
        {
            Console.WriteLine("Цепочка " + input + " не принята автоматом");
        }
    }
}

class Program
{
    static void Main(string[] args)
    {
        Automaton automaton = new Automaton();

        Console.WriteLine("Грамматика:\r\n" +
            "S -> 0S | S1S | S1E1 | 0E1\r\n" +
            "A -> 0A | A1A | A1B | 0B\r\n" +
            "B -> 0C | 1D\r\n" +
            "C -> 0\r\n" +
            "D -> 1\r\n" +
            "E -> 0E | 1");
        Console.WriteLine("");


        string input; // вводимая цепочка

        while (true)
        {
            Console.WriteLine("Для выхода напишите stop");
            Console.Write("Введите цепочку: ");

            input = Console.ReadLine();

            if (input.ToLower().Trim() == "stop")
                break;

            if (input.Trim() != "")
                automaton.Run(input);
        }
    }
}