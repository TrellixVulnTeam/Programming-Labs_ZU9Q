using Xunit;
using Tree;

namespace tests
{
    public class DuplicableBSTreeTests
    {
        private DuplicableSimpleBSTree<int, int> tree = new DuplicableSimpleBSTree<int, int>();

        public DuplicableBSTreeTests()
        {
            tree.Add(4, 4);
            tree.Add(9, 9);
            tree.Add(10, 10);
            tree.Add(8, 8);
            tree.Add(1, 1);
        }

        [Fact]
        public void Add()
        {
            tree.Add(4, 4);
            tree.Add(1, 1);
            tree.Add(1, 1);
            Assert.Equal(2, tree.GetKeyCount(4));
            Assert.Equal(3, tree.GetKeyCount(1));
            Assert.Equal(1, tree.GetKeyCount(8));
            Assert.Equal(1, tree.GetKeyCount(9));
            Assert.Equal(1, tree.GetKeyCount(10));
        }

        [Fact]
        public void Remove()
        {
            tree.Add(4, 4);
            tree.Add(1, 1);
            tree.Add(1, 1);

            tree.Remove(4);
            tree.Remove(1);
            tree.Remove(8);

            Assert.Equal(9, tree.Root.Key);
            Assert.Equal(10, tree.Root.Right.Key);
            Assert.Null(tree.Root.Left);
            Assert.Null(tree.Root.Right.Left);
            Assert.Null(tree.Root.Right.Right);
        }

        [Fact]
        public void AddNull()
        {
            var tree = new DuplicableSimpleBSTree<string, string>();
            Assert.Throws<System.ArgumentNullException>(() => tree.Add(null, "smt"));
            Assert.Throws<System.ArgumentNullException>(() => tree.Add("smt", null));
            Assert.Throws<System.ArgumentNullException>(() => tree.Add(null, null));
        }

        [Fact]
        public void RemoveNullKey()
        {
            var tree = new DuplicableSimpleBSTree<string, string>();
            Assert.Throws<System.ArgumentNullException>(() => tree.Remove(null));
        }

        [Fact]
        public void TraverseInOrder()
        {
            var tree = new DuplicableSimpleBSTree<int, int>();
            tree.Add(4, 4);
            tree.Add(9, 9);
            tree.Add(10, 10);
            tree.Add(8, 8);
            tree.Add(1, 1);
            tree.Add(4, 4);
            tree.Add(3, 3);

            int[] correct = { 1, 3, 4, 4, 8, 9, 10 };
            int i = 0;
            foreach (var node in tree.InOrderTraversal())
            {
                Assert.Equal(correct[i], node.Key);
                i++;
            }
        }

        [Fact]
        public void TraversePostOrder()
        {
            var tree = new DuplicableSimpleBSTree<int, int>();
            tree.Add(4, 4);
            tree.Add(9, 9);
            tree.Add(10, 10);
            tree.Add(8, 8);
            tree.Add(1, 1);
            tree.Add(9, 9);
            tree.Add(3, 3);

            int[] correct = { 3, 1, 8, 10, 9, 9, 4 };
            int i = 0;
            foreach (var node in tree.PostOrderTraversal())
            {
                Assert.Equal(correct[i], node.Key);
                i++;
            }
        }

        [Fact]
        public void TraverseBFS()
        {
            var tree = new DuplicableSimpleBSTree<int, int>();
            tree.Add(4, 4);
            tree.Add(9, 9);
            tree.Add(10, 10);
            tree.Add(8, 8);
            tree.Add(1, 1);
            tree.Add(10, 10);
            tree.Add(3, 3);

            int[] correct = { 4, 1, 9, 3, 8, 10, 10 };
            int i = 0;
            foreach (var node in tree.BFS())
            {
                Assert.Equal(correct[i], node.Value);
                i++;
            }
        }

        [Fact]
        public void TraverseDFS()
        {
            var tree = new DuplicableSimpleBSTree<int, int>();
            tree.Add(4, 4);
            tree.Add(9, 9);
            tree.Add(10, 10);
            tree.Add(8, 8);
            tree.Add(1, 1);
            tree.Add(3, 3);
            tree.Add(8, 8);

            int[] correct = { 4, 1, 3, 9, 8, 8, 10 };
            int i = 0;
            foreach (var node in tree.DFS())
            {
                Assert.Equal(correct[i], node.Key);
                i++;
            }
        }
    }
}