Name:       faster
Version:    0.1
Release:    1%{?dist}
Summary:    Disable BD PROCHOT for Linux
License:    CC-BY-SA
URL:        https://github.com/moceap/Faster
Source0:    faster.c
Source1:    faster.service

%description
Disable BD PROCHOT for Linux

%prep

%build
gcc %{SOURCE0} -o faster

%install
mkdir -p %{buildroot}%{_bindir}
mkdir -p %{buildroot}%{_sysconfdir}/systemd/system
cp -pr %{name} %{buildroot}%{_bindir}
cp -pr %{SOURCE1} %{buildroot}%{_sysconfdir}/systemd/system

%post
systemctl enable faster.service
systemctl start faster.service

%files
%{_bindir}/%{name}
%{_sysconfdir}/systemd/system/faster.service

%changelog
* Sat Aug 31 2019 Mosaab Alzoubi <moceap<at>hotmail<dot>com> - 0.1-1
- Initial packaging
