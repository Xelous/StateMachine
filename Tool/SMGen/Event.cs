using System;

namespace xelous
{
    public class Event
    {
        private string mName;

        public Event(string pName)
        {
            mName = pName;
        }

        public string Name
        {
            get { return mName; }
            set { mName = value; }
        }
    }
}