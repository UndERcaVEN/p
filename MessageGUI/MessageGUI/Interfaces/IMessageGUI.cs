using System.Runtime.InteropServices;

namespace MessageGUI
{
    [ComVisible(true)]
    public interface IMessageGUI
    {
        string message { get; }
        void Initialize();
        void DisplayMessage(string message);
        void ClearMessage();
    }
}
