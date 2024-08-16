"""Module containing tests for the Ftd2xxDevice class."""

from e_lims_d2xx import Ftd2xxDevice


def test_get_infos() -> None:
    """Check the device infos are correct."""
    ft = Ftd2xxDevice().get_information(0)

    flags, device_type, device_id, loc_id, serial_number, description = ft
    assert isinstance(flags, int)
    assert isinstance(device_type, int)
    assert isinstance(device_id, int)
    assert isinstance(loc_id, int)
    assert isinstance(serial_number, str)
    assert isinstance(description, str)

if __name__ == "__main__":
    ft = Ftd2xxDevice().get_information(0)
    print(ft)