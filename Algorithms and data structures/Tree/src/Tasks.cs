using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Linq;

namespace Tree
{
    public static class Tasks
    {
        public static string GetConsolePrintString<TKey, TValue>(this DuplicableSimpleBSTree<TKey, TValue> tree)
                    where TKey : IComparable<TKey>
        {
            if (tree == null)
                throw new ArgumentNullException("Tree is null");
            if (tree.Root == null)
                throw new ArgumentException("Tree is empty");

            return GetConsolePrintNodeString(tree.Root, tree as DuplicableSimpleBSTree<TKey, TValue>);
        }

        public static string GetConsolePrintNodeString<TKey, TValue>(BSTNode<TKey, TValue> node, DuplicableSimpleBSTree<TKey, TValue> tree)
                        where TKey : IComparable<TKey>
        {
            var builder = new StringBuilder(new string(' ', 2 * node.Depth));

            builder.AppendLine($"- {node.ToString()} - {tree.GetKeyCount(node.Key)}");

            if (node.Left != null)
                builder.Append(GetConsolePrintNodeString(node.Left, tree));
            else if (node.Right != null)
                builder.AppendLine(new string(' ', 2 * node.Depth + 2) + '-');

            if (node.Right != null)
                builder.Append(GetConsolePrintNodeString(node.Right, tree));
            else if (node.Left != null)
                builder.AppendLine(new string(' ', 2 * node.Depth + 2) + '-');

            return builder.ToString();
        }

        public static DuplicableSimpleBSTree<char, char> GenerateFromString(string text)
        {
            var tree = new DuplicableSimpleBSTree<char, char>();
            foreach (var symbol in text)
            {
                tree.Add(symbol, symbol);
            }

            return tree;
        }

        public static DuplicableSimpleBSTree<string, string> GenerateFromText(string text)
        {
            var tree = new DuplicableSimpleBSTree<string, string>();
            foreach (var symbol in text.Split(' ', '\t', '\n'))
            {
                tree.Add(symbol, symbol);
            }

            return tree;
        }

        public static DuplicableSimpleBSTree<int, char> GenerateLabExpressionTree()
        {
            var tree = new DuplicableSimpleBSTree<int, char>(1, '+');
            tree.Add(0, '9');
            tree.Add(3, '*');
            tree.Add(2, '8');
            tree.Add(5, '+');
            tree.Add(4, '7');
            tree.Add(15, '+');
            tree.Add(16, '1');
            tree.Add(11, '-');
            tree.Add(13, '-');
            tree.Add(12, '3');
            tree.Add(14, '2');
            tree.Add(7, '*');
            tree.Add(6, '6');
            tree.Add(9, '+');
            tree.Add(8, '5');
            tree.Add(10, '4');

            return tree;
        }

        public static IEnumerable<BSTNode<string, string>> GetAllStartWith(this DuplicableSimpleBSTree<string, string> tree, char letter)
        {
            if (tree == null)
                throw new ArgumentNullException("Tree is null");

            return tree.BFS().Distinct().Where(node => node.Key[0] == letter);
        }

        public static void WriteText(this DuplicableSimpleBSTree<string, string> tree, Stream stream)
        {
            using (var writer = new StreamWriter(stream))
            {
                foreach (var item in tree.BFS())
                {
                    writer.WriteLine(item.Value);
                }
            }
        }
    }
}