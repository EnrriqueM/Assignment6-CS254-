//Leaving output in console instead of file for testing purposes.
void output(fileRead log1)
{
	int words = 0;
    int count = log1.getAddress().size();
    for (int i = 0; i < count; i++)
    {
		cout << log1.getCycle()[i] << " " << log1.getType()[i] << " command: ";
	}
}
