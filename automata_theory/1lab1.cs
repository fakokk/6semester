﻿using System;
using System.Text;
using System.Collections.Generic;
using System.Text.RegularExpressions;

namespace Lab_1
{
	class Program
	{
		/// <summary>
		/// Правило языка
		/// </summary>
		public class Rule {
			/// <summary>
			/// Порождающая цепочка языка
			/// </summary>
			public string Key { get; set; }
			/// <summary>
			/// Порождаемая цепочка языка
			/// </summary>
			public string Value { get; set; }
			/// <summary>
			/// Введет ли правило зацикливанию.
			/// True - введет, false - правило не зацикливает грамматику
			/// </summary>
			public bool IsLooped { get; set; }

			public Rule(string k, string v, bool l = false) {
				Key = k;
				Value = v;
				IsLooped = l;
			}
		}


		public static void PrintRules(List<Rule> R)
        {
			Console.WriteLine("Правила для языка");
			for (int i = 0; i < R.Count; i++)
			{
				Console.WriteLine("   \u2022" + R[i].Key + "-->" + R[i].Value);
			}
		}
		/// <summary>
		/// Класс формального языка с леволинейной грамматикой и проверкой на зацикливание
		/// </summary>
		public class FormalLanguage {

			/// <summary>
			/// Правила языка
			/// </summary>
			private List<Rule> _rules { get; set; }
			/// <summary>
			/// Максимально количество повторений
			/// </summary>
			public uint MaxRepetitionsCount { get; set; }

			public FormalLanguage(List<Rule> rules, uint count = 10000) {
				_rules = rules;
				MaxRepetitionsCount = count;
			}
			/*
			/// <summary>
			/// Проверяет правило на зацикливание
			/// </summary>
			/// <param name="input">Строка, к которой применяется правило</param>
			/// <param name="rule">Правило языка</param>
			/// <param name="count">Количество допустимых повторений</param>
			/// <returns>true - если правило зацикливает перевод, иначе - false</returns>
			private bool CheckLoop(string input, Rule rule, int count = 5) {
				for (int i = 0; i < count; i++) {
					string key = rule.Key;
					string value = rule.Value;

					int pos = input.IndexOf(key);

					if (pos != -1)
					{
						input = input.Remove(pos, key.Length);
						input = input.Insert(pos, value);
					}
					else return false;				
				}

				return true;
			}

			*/
			/// <summary>
			/// Лвеосторонний вывод.
			/// </summary>
			/// <returns>Строка, порожденная на основе правил языка.</returns>
			public string OutputLeft()
			{

				string result = "S";
				int count = 0;
				while (count < MaxRepetitionsCount)
				{
					int pos = -1;

					// найдем крайний левый нетерминальный символ в цепочке
					foreach (Rule rule in _rules)
					{
						string key = rule.Key;
						int findPos = result.IndexOf(key);
						if ((pos > findPos || pos == -1) && findPos != -1)
						{
							pos = findPos;
						}

					}

					// если не найдено ниодного подходящего правила - выходим
					if (pos == -1)
					{
						break;
					}

					// найдем все правил подходящие для крайнего левого нетерминального символа
					List<Rule> rules = new();
					foreach (Rule rule in _rules)
					{
						string key = rule.Key;
						if (pos == result.IndexOf(key))
						{
							rules.Add(rule);
						}
					}

					// случайно выберем правило
					Random random = new();
					int index = random.Next(rules.Count);
					Rule r = rules[index];

					int p = result.IndexOf(r.Key);
					result = result.Remove(p, r.Key.Length);
					result = result.Insert(p, r.Value);

					count++;
				}

				return result;
			}
		}
		/// <summary>
		/// Грамматика формального языка
		/// </summary>
		public class Grammar {
			/// <summary>
			/// Множество терминальных символов
			/// </summary>
			public List<string> Nonterminal { get; set; }
			/// <summary>
			/// Множество терминальных символов
			/// </summary>
			public List<string> Terminal { get; set; }
			/// <summary>
			/// Множество правил (продукций) грамматики
			/// </summary>
			public List<Rule> P { get; set; }
			/// <summary>
			/// Целевой (начальный) символ грамматики
			/// </summary>
			public string S { get; set; }
			/// <summary>
			/// 
			/// </summary>
			/// <param name="vn">Нетерминальные символы</param>
			/// <param name="vt">Nthvbyfkmyst cbvdjks</param>
			/// <param name="rules">Правила</param>
			/// <param name="s">Начальный символ</param>
			public Grammar(List<string> vn, List<string> vt, List<Rule> rules, string s = "S") {
				Nonterminal = vn;
				Terminal = vt;
				P = rules;
				S = s;
			}
			/// <summary>
			/// Возвращает тип грамматики
			/// </summary>
			/// <returns></returns>
			/// 
			
			public string GetTypeGrammar() {
				bool isTypeOne = true;
				bool isTypeTwo = true;
				bool isTypeThree = true;

				bool isEachTermPosBigger = true;
				bool isEachTermPosSmaller = true;
				foreach (Rule r in P) {
					// проверка проинадлежности первому типу грамматики
					isTypeOne &= r.Key.Length <= r.Value.Length;

					// проверка принадлежности второму типу
					foreach (string vt in Terminal) {
						isTypeTwo &= !r.Key.Contains(vt);
					}
					
					if (isEachTermPosBigger || isEachTermPosSmaller)
					{
						List<int> terminlPositions = new();
						List<int> nonTerminlPositions = new();
						foreach (string vn in Nonterminal)
						{						
							int TEMP = r.Value.IndexOf(vn);
							if(TEMP != -1) { nonTerminlPositions.Add(TEMP); }
						}
						foreach (string vt in Terminal)
						{
							int TEMP = r.Value.IndexOf(vt);
							if (TEMP != -1) { terminlPositions.Add(TEMP); }	
						}
						foreach (int pos in terminlPositions)
						{
							foreach (int posNonTerm in nonTerminlPositions)
							{
								isEachTermPosBigger &= pos > posNonTerm;
								isEachTermPosSmaller &= pos < posNonTerm;
							}
						}
						if((isEachTermPosBigger == false)&&(isEachTermPosSmaller==false))
                        {
							isTypeThree = false;
                        }
					}
				}
				Console.WriteLine("Относится к типам по Хомскому:");
				string res = "0";
				if (isTypeOne) res += " 1";
				if (isTypeTwo) res += " 2";
				if (isTypeThree) res += " 3";
				return res;
			}
			
			/// <summary>
			/// Создает дерево вывода из цепочки символов
			/// </summary>
			/// <param name="text">Строка (цепочка символов), для которой нужно построить дерево</param>
			/// <returns></returns>
			public string MakeTree(string text)
			{
				int maxCount = 10000;
				int count = 0;
				List<string> tree = new();
				tree.Add(text);
				while (count < maxCount)
				{
					foreach (Rule rule in P)
					{
						string key = rule.Key;
						string value = rule.Value;

						int pos = text.LastIndexOf(value);
						if (pos != -1)
						{
							text = text.Remove(pos, value.Length);
							text = text.Insert(pos, key);

							string separator = "|";
							for (int i = 0; i < pos; i++)
							{
								separator = " " + separator;
							}
							tree.Add(separator);
							tree.Add(text);
						}
					}
					count++;
				}
				tree.Reverse();

				foreach (string branch in tree)
				{
					Console.WriteLine(branch);
				}
				return text;
			}

		}
	
		static void Main(string[] args)
		{
			Console.OutputEncoding = Encoding.Unicode;

			Console.WriteLine("Первая лабораторная работа.");

			Console.WriteLine("Задание 11.");
			Console.WriteLine("Подпункт а)");
			Console.WriteLine("Грамматика описывает язык 0^n 1^n 'Символ перепендикуляра' 9");
			List<Rule>  dict = new()
			{
				new Rule("S", "0S"),
				new Rule("S", "0B"),
				new Rule("B", "1B"),
				new Rule("B", "1C"),
				new Rule("C", "1C"),
				new Rule("C", "9"),

			};
			FormalLanguage fl = new(dict);

			fl = new(dict);
			Console.WriteLine(fl.OutputLeft());

			dict = new()
			{
				new Rule("S", "A9"),
				new Rule("A", "A1"),
				new Rule("A", "CB1"),
				new Rule("B", "B1"),
				new Rule("B", "C1"),
				new Rule("B", "CB1"),
				new Rule("C", "0"),

			};
			fl = new(dict);

			Console.WriteLine(fl.OutputLeft());

			Console.WriteLine("Подпункт б)");
			Console.WriteLine("Грамматика описывает язык {a^n b^n} 'Символ перепендикуляра'9");
			dict = new()
			{
				new Rule("S", "aA"),
				new Rule("S", "aB"),
				new Rule("S", "bA"),
				new Rule("A", "bS"),
				new Rule("B", "aS"),
				new Rule("B", "bB"),
				new Rule("B", "9"),

			};
			fl = new(dict);
			Console.WriteLine(fl.OutputLeft());

			dict = new()
			{
				new Rule("S", "A9"),
				new Rule("A", "Ba"),
				new Rule("A", "Bb"),
				new Rule("A", "Ab"),
				new Rule("A", "ABa"),
				new Rule("A", "ABb"),
				new Rule("B", "a"),
				new Rule("B", "b"),

			};
			fl = new(dict);
			Console.WriteLine(fl.OutputLeft());
			Console.WriteLine();
		}
	}
}
