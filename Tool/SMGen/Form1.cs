using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using xelous;

namespace SMGen
{
    public partial class Form1 : Form
    {
        private List<StateMachine> mStateMachineList = new List<StateMachine>();
        private List<State> mStateList = new List<State>();

        public Form1()
        {
            InitializeComponent();
        }

        private void OnLoad(object sender, EventArgs e)
        {
            StateMachineAreaResize();
        }

        private void OnSizeChanged(object sender, EventArgs e)
        {
            StateMachineAreaResize();   
        }

        private void StateMachineAreaResize()
        {            
            mStateMachines.Size = new Size(mStateMachines.Width, this.Height - mStateMachines.Location.Y - 80);
            mStates.Size = new Size(mStates.Width, this.Height - mStates.Location.Y - 80);

            mAddStateMachineButton.Location = new Point(mAddStateMachineButton.Location.X, this.Height - mStateMachines.Location.Y - 50);
            mDeleteStateMachineButton.Location = new Point(mDeleteStateMachineButton.Location.X, mAddStateMachineButton.Location.Y);

            mAddStateButton.Location = new Point(mAddStateButton.Location.X, mAddStateMachineButton.Location.Y);
            mDeleteStateButton.Location = new Point(mDeleteStateButton.Location.X, mAddStateMachineButton.Location.Y);
        }

        private void AddStateMachineButtonClicked(object sender, EventArgs e)
        {
            Point p = PointToScreen(mStateMachines.Location);
            CreateBox cb = new CreateBox();            
            if (cb.ShowDialog() == DialogResult.OK )
            {
                string theText = cb.GetContents();
                StateMachine sm = new StateMachine(theText);
                mStateMachineList.Add(sm);
                UpdateStateMachineList();
            }
            cb.Dispose();
        }

        private void AddStateButtonClicked(object sender, EventArgs e)
        {
            Point p = PointToScreen(mStateMachines.Location);
            CreateBox cb = new CreateBox();
            if (cb.ShowDialog() == DialogResult.OK)
            {
                string theText = cb.GetContents();
                State s = new State(theText);
                mStateList.Add(s);
                UpdateStateList();
            }
            cb.Dispose();
        }

        public void OnKeyDown(object sender, KeyEventArgs e)
        {
            if (e.Control)
            {
                if (e.KeyCode == Keys.A)
                {
                    AddStateMachineButtonClicked(this, new EventArgs());
                }
                else if (e.KeyCode == Keys.S)
                {
                    AddStateButtonClicked(this, new EventArgs());
                }
            }
        }

        private delegate void VoidDelegate();

        private void UpdateStateMachineList()
        {
            if (this.InvokeRequired)
            {
                this.Invoke(new VoidDelegate(UpdateStateMachineList));
            }
            else
            {
                mStateMachines.Items.Clear();
                foreach(StateMachine s in mStateMachineList)
                {
                    mStateMachines.Items.Add(s.ToString());
                }
            }
        }

        private void UpdateStateList()
        {
            if (this.InvokeRequired)
            {
                this.Invoke(new VoidDelegate(UpdateStateList));
            }
            else
            {
                mStates.Items.Clear();
                foreach(State s in mStateList)
                {
                    mStates.Items.Add(s.ToString());
                }
            }
        }

        private void OnAddState(object sender, EventArgs e)
        {
            AddStateButtonClicked(this, e);
        }

        private void OnDeleteState(object sender, EventArgs e)
        {

        }
    }
}
